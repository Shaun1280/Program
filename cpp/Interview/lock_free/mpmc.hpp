#include <atomic>
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>

template <typename T, size_t capacity_> class MPMCLockFreeRingBuffer {
    static_assert(capacity_ >= 1,
                  "capacity must be greater than or equal to 1");
    constexpr static size_t capacity = capacity_ + 1;

  public:
    MPMCLockFreeRingBuffer()
        : m_buffer(capacity), m_ticket(capacity), m_head(0), m_tail(0) {}

    template <typename... Args> bool emplace(Args&&... args) {
        static_assert(std::is_constructible_v<T, Args...>,
                      "T must be constructible with Args...");

        auto tail = m_tail.load(std::memory_order_relaxed);
        auto const head = m_head.load(std::memory_order_acquire);

        if ((tail + 1) % capacity == head % capacity) {
            return false;
        }

        tail = m_tail.fetch_add(1);

        auto const _idx = idx(tail);
        auto const _turn = turn(tail);
        while (_turn * 2 != m_ticket[_idx].load(std::memory_order_acquire))
            ;
        m_buffer[_idx] = std::move(T(std::forward<Args>(args)...));
        m_ticket[_idx].store(_turn * 2 + 1, std::memory_order_release);

        return true;
    }

    // Dequeue an item from the queue (head increases)
    bool pop(T& item) noexcept {
        auto head = m_head.load(std::memory_order_relaxed);
        auto const tail = m_tail.load(std::memory_order_acquire);

        if (head == tail) {
            return false;
        }

        head = m_head.fetch_add(1);

        auto const _idx = idx(head);
        auto const _turn = turn(head);
        while (_turn * 2 + 1 != m_ticket[_idx].load(std::memory_order_acquire))
            ;
        item = std::move(m_buffer[_idx]);
        m_ticket[_idx].store(_turn * 2 + 2, std::memory_order_release);
        return true;
    }

    size_t size() {
        size_t head = m_head.load(std::memory_order_relaxed);
        size_t tail = m_tail.load(std::memory_order_acquire);
        return (tail - head) % capacity;
    }

    bool empty() {
        return m_head.load(std::memory_order_relaxed) ==
               m_tail.load(std::memory_order_acquire);
    }

    constexpr size_t idx(size_t i) const noexcept { return i % capacity; }
    constexpr size_t turn(size_t i) const noexcept { return i / capacity; }

  private:
    std::vector<T> m_buffer;
    std::vector<std::atomic<size_t>> m_ticket;
    std::atomic<size_t> m_head;
    std::atomic<size_t> m_tail;
};

// int main() {
//     MPMCLockFreeRingBuffer<int, 8> queue; // 环形缓冲区的容量为 8

//     // 启动多个生产者线程
//     std::vector<std::thread> producers;
//     for (int i = 0; i < 3; ++i) {
//         producers.emplace_back([&queue, i]() {
//             for (int j = 0; j < 10; ++j) {
//                 while (!queue.enqueue(i * 10 + j)) {
//                     // busy-wait if the queue is full
//                 }
//                 std::cout << "Producer " + std::to_string(i) +
//                                  " produced: " + std::to_string(i * 10 + j) +
//                                  "\n";
//             }
//         });
//     }

//     // 启动多个消费者线程
//     std::vector<std::thread> consumers;
//     for (int i = 0; i < 3; ++i) {
//         consumers.emplace_back([&queue, i]() {
//             for (int j = 0; j < 10; ++j) {
//                 int item;
//                 while (!queue.pop(item)) {
//                     // busy-wait if the queue is empty
//                 }
//                 std::cout << "Consumer " + std::to_string(i) +
//                                  " consumed: " + std::to_string(item) + "\n";
//             }
//         });
//     }

//     // 等待所有生产者和消费者线程结束
//     for (auto& producer : producers) {
//         producer.join();
//     }
//     for (auto& consumer : consumers) {
//         consumer.join();
//     }

//     return 0;
// }