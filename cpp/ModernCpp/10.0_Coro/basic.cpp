#include <coroutine>
#include <future>
#include <iostream>

struct ReturnObject {
    struct promise_type {
        ReturnObject get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        void return_void() {}
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