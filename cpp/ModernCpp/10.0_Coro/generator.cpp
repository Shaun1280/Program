#include <coroutine>
#include <iostream>
#include <utility>

struct Generator { // ReturnObject
    // 协程执行完成之后，外部读取值时抛出的异常
    class ExhaustedException : std::exception {};

    struct promise_type { // Return Object should have a promise_type nested
                          // type
        int current_value;
        bool is_ready = false;

        // 构造协程的返回值类型
        Generator get_return_object() {
            return Generator{
                std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        // 传值的同时要挂起，值存入 value 当中, e.g. co_wait 1;
        std::suspend_always await_transform(int value) {
            this->current_value = value;
            this->is_ready = true;
            return {};
        }

        // e.g. co_yield 1;
        std::suspend_always yield_value(int value) {
            this->current_value = value;
            this->is_ready = true;
            return {};
        }

        // 开始执行时不挂起，执行到第一个挂起点
        std::suspend_never initial_suspend() { return {}; }

        // 执行结束后不需要挂起
        std::suspend_always final_suspend() noexcept { return {}; }

        // 没有返回值
        void return_void() {}

        // 为了简单，我们认为序列生成器当中不会抛出异常，这里不做任何处理
        void unhandled_exception() {}
    };

    std::coroutine_handle<promise_type> handle;

    explicit Generator(std::coroutine_handle<promise_type> handle) noexcept
        : handle(handle) {}

    Generator(Generator&& generator) noexcept
        : handle(std::exchange(generator.handle, {})) {}

    Generator(Generator&) = delete;
    Generator& operator=(Generator&) = delete;

    bool has_next() {
        // 协程已经执行完成
        if (!handle || handle.done()) {
            return false;
        }

        // 协程还没有执行完成，并且下一个值还没有准备好
        if (!handle.promise().is_ready) {
            handle.resume();
        }

        if (handle.done()) {
            // 恢复执行之后协程执行完，这时候必然没有通过 co_await 传出值来
            return false;
        } else {
            return true;
        }
    }

    int next() {
        if (has_next()) {
            // 此时一定有值，is_ready 为 true
            // 消费当前的值，重置 is_ready 为 false
            handle.promise().is_ready = false;
            return handle.promise().current_value;
        }
        throw ExhaustedException();
    }

    ~Generator() {
        if (handle) {
            handle.destroy();
        }
    }
};

Generator sequence() {
    int i = 0;
    while (true) {
        co_yield i++;
    }
}

int main() {
    auto generator = sequence();
    for (int i = 0; i < 10; ++i) {
        if (generator.has_next()) {
            std::cout << generator.next() << std::endl;
        } else
            break;
    }
    return 0;
}