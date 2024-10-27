#include <coroutine>
#include <future>
#include <iostream>

struct ReturnObject {
    struct promise_type {
        ReturnObject get_return_object() {
            // 创建 Result 对象
            /**
             * 协程的返回值并不是在返回之前才创建，而是在协程的状态创建出来之后马上就创建的。也就是说，协程的状态被创建出来之后，会立即构造
             * promise_type 对象，进而调用 get_return_object 来创建返回值对象。
             */
            return {};
        }

        std::suspend_never initial_suspend() {
            /**
             * 协程体执行的第一步是调用 co_await
             * promise.initial_suspend()，initial_suspend
             * 的返回值就是一个等待对象（awaiter），如果返回值满足挂起的条件，则协程体在最一开始就立即挂起
             */
            return {};
        }

        std::suspend_never final_suspend() noexcept {
            /**
             * 当协程执行完成或者抛出异常之后会先清理局部变量，接着调用
             * final_suspend 来方便开发者自行处理其他资源的销毁逻辑
             */
            return {};
        }

        void unhandled_exception() {
            // exception_ = std::current_exception(); // 获取当前异常
        }

        // void return_value(int value) 用于设置协程的返回值 co_return value;
        void return_void() {} // co_return;
    };
};

struct Awaiter {
    int value;

    bool await_ready() {
        // 协程挂起
        return false; // 返回 false，总是挂起; 返回 true，总是不挂起
    }

    void await_suspend(std::coroutine_handle<> coroutine_handle) {
        // 切换线程
        std::async(std::launch::async, [=]() {
            using namespace std::chrono_literals;
            // sleep 1s
            std::this_thread::sleep_for(1s);
            // 恢复协程
            coroutine_handle.resume();
        });
    }

    int await_resume() {
        // value 将作为 co_await 表达式的值
        return value;
    }
};

ReturnObject test() {
    std::cout << "Hello, " << std::endl;
    std::cout << co_await Awaiter{.value = 42} << std::endl;
    std::cout << "World!" << std::endl;
}

int main() {
    test();
    return 0;
}