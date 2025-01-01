#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class ThreadSafePrinter {
  private:
    std::queue<std::function<void()>> print_tasks;
    std::mutex mutex;
    std::condition_variable cv;
    bool stop = false;
    std::thread printer_thread;

    void printer_loop() {
        while (true) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(mutex);
                cv.wait(lock,
                        [this]() { return !print_tasks.empty() || stop; });

                if (stop && print_tasks.empty()) {
                    break;
                }

                task = std::move(print_tasks.front());
                print_tasks.pop();
            }
            task(); // 执行打印任务
        }
    }

  public:
    ThreadSafePrinter()
        : printer_thread(&ThreadSafePrinter::printer_loop, this) {}

    ~ThreadSafePrinter() {
        {
            std::lock_guard<std::mutex> lock(mutex);
            stop = true;
        }
        cv.notify_one();
        if (printer_thread.joinable()) {
            printer_thread.join();
        }
    }

    template <typename... Args> void print(Args&&... args) {
        auto print_func = [... args = std::forward<Args>(args)]() {
            (std::cout << ... << args);
        };

        {
            std::lock_guard<std::mutex> lock(mutex);
            print_tasks.push(std::move(print_func));
        }
        cv.notify_one();
    }
};

// 使用示例
int main() {
    ThreadSafePrinter printer;

    // 工作线程
    std::thread worker([&printer]() {
        for (int i = 0; i < 5; i++) {
            printer.print("Worker thread: ", i, " Hello!\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    // 主线程
    for (int i = 0; i < 5; i++) {
        printer.print("Main thread: ", i, " World!\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    worker.join();
    return 0;
}