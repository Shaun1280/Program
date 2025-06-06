#include <iostream> // std::cout std::endl;
#include <memory>   // std::make_shared
#include <queue>    // std::queue
#include <vector>   // std::vector

#include <condition_variable> // std::condition_variable
#include <future>             // std::future, std::packaged_task
#include <mutex>              // std::mutex, std::unique_lock
#include <thread>             // std::thread

#include <functional> // std::function, std::bind
#include <stdexcept>  // std::runtime_error
#include <utility>    // std::move, std::forward

class ThreadPool {
  public:
    // initialize the number of concurrency threads
    ThreadPool(size_t);

    // enqueue new thread task
    template <class F, class... Args>
    decltype(auto) enqueue(F&& f, Args&&... args);

    // destroy thread pool and all created threads
    ~ThreadPool();

  private:
    // thread list, stores all threads
    std::vector<std::thread> workers;
    // queue task, the type of queue elements are functions with void return
    // type
    std::queue<std::function<void()>> tasks;

    // for synchonization
    std::mutex queue_mutex;
    // std::condition_variable is a new feature from c++11,
    // it's a synchronization primitives. it can be used
    // to block a thread or threads at the same time until
    // all of them modified condition_variable.
    std::condition_variable condition;
    bool stop;
};

// constructor initialize a fixed size of worker
inline ThreadPool::ThreadPool(size_t threads) : stop(false) {
    // initialize worker
    for (size_t i = 0; i < threads; ++i)
        // std::vector::emplace_back :
        //    append to the end of vector container
        //    this element will be constructed at the end of container, without
        //    copy and move behavior
        workers.emplace_back([this] { // the lambda express capture this, i.e.
                                      // the instance of thread pool
            // avoid fake awake
            while (true) {
                // define function task container, return type is void
                std::function<void()> task;

                // critical section
                {
                    // get mutex
                    std::unique_lock<std::mutex> lock(this->queue_mutex);

                    // block current thread
                    this->condition.wait(lock, [this] {
                        return this->stop || !this->tasks.empty();
                    });

                    // return if queue empty and task finished
                    if (this->stop && this->tasks.empty())
                        return;

                    // otherwise execute the first element of queue
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }

                // execution
                task();
            }
        });
}

// Enqueue a new thread
// use variadic templates and tail return type
template <class F, class... Args>
decltype(auto) ThreadPool::enqueue(F&& f, Args&&... args) {
    // deduce return type
    using return_type = std::invoke_result_t<F, Args...>;

    // fetch task, can use std::bind(std::forward<F>(f),
    // std::forward<Args>(args)...) to replace lambda expression
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        // use lambda expression to bind function and arguments
        [func = std::forward<F>(f),
         ... largs = std::forward<Args>(args)]() mutable {
            return std::invoke(std::move(func), std::move(largs)...);
        });

    // package_task::get_future() returns a future object
    std::future<return_type> result = task->get_future();

    // critical section
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // avoid add new thread if theadpool is destroyed
        if (stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");

        // add thread to queue
        tasks.emplace([task] { (*task)(); });
    }

    // notify a wait thread
    condition.notify_one();
    return result;
}

// destroy everything
ThreadPool::~ThreadPool() {
    // critical section
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }

    // wake up all threads
    condition.notify_all();

    // let all processes into synchronous execution, use c++11 new for-loop:
    // for(value:values)
    for (std::thread& worker : workers)
        worker.join();
};

int main() {
    ThreadPool pool(4);
    auto result = pool.enqueue([](int answer) { return answer; }, 42);
    std::cout << "The answer is " << result.get() << std::endl;
    return 0;
}