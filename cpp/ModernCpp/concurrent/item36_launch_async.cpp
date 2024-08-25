#include <future>
#include <iostream>
#include <type_traits>

// Specify std::launch::async if asynchronicity is essential.
namespace item36 {
    /**
     * std::async的默认启动策略是异步和同步执行兼有的。
     * 这个灵活性导致访问thread_locals的不确定性，隐含了任务可能不会被执行的意思，会影响调用基于超时的wait的程序逻辑。
     * 如果异步执行任务非常关键，则指定std::launch::async。
     */
    void deferCase() {
        using namespace std::literals;
        auto f = []() { return 1; };
        auto fut = std::async(f);
        if (fut.wait_for(0s) == std::future_status::deferred) {
            std::cout << fut.get() << std::endl;
        } else {
            while (fut.wait_for(100ms) != std::future_status::ready) {
                // task没 deferred（被延迟），也没ready（已准备）
                // 做并行工作直到已准备
            }
            // fut是ready（已准备）状态
            std::cout << fut.get() << std::endl;
        }
    }

    template <typename F, typename... Ts>
    inline std::future<typename std::result_of<F(Ts...)>::type> really_async(F&& f,
                                                                             Ts&&... params) {
        return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
    }

    template <typename F, typename... Ts>
    inline auto really_async2(F&& f, Ts&&... params) {
        return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
    }
}  // namespace item39

int main() {
    return 0;
}