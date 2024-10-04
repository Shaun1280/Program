#include <atomic>
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>

template <typename T, size_t capacity> class MPMCLockFreeRingBuffer {
  public:
    MPMCLockFreeRingBuffer()
        : capacity_(capacity), buffer_(capacity), head_(0), tail_(0) {
        // capacity must be greater than 1 and a power of 2 for this
        // implementation
        assert((capacity > 1));
    }

    // Enqueue an item to the queue (tail increases)
    bool enqueue(const T& item) {
        size_t tail;
        size_t next_tail;

        while (op_.load()) {
        }
        op_.store(true);

        do {
            tail = tail_.load(std::memory_order_relaxed);
            next_tail = (tail + 1) % capacity_;

            size_t head = head_.load(std::memory_order_acquire);
            if (next_tail == head) {
                return false; // Queue is full
            }
        } while (!tail_.compare_exchange_weak(tail, next_tail,
                                              std::memory_order_release,
                                              std::memory_order_relaxed));

        buffer_[tail] = item; // Store the item at the current tail position
        op_.store(false);
        return true;
    }

    template <typename... Args> bool emplace(Args&&... args) {
        size_t tail;
        size_t next_tail;

        while (op_.load()) {
        }
        op_.store(true);

        do {
            tail = tail_.load(std::memory_order_relaxed);
            next_tail = (tail + 1) % capacity_;

            size_t head = head_.load(std::memory_order_acquire);
            if (next_tail == head) {
                return false; // Queue is full
            }
        } while (!tail_.compare_exchange_weak(tail, next_tail,
                                              std::memory_order_release,
                                              std::memory_order_relaxed));

        buffer_[tail] = T(std::forward<Args>(
            args)...); // Store the item at the current tail position
        op_.store(false);
        return true;
    }

    // Dequeue an item from the queue (head increases)
    bool pop(T& item) {
        size_t head;
        size_t next_head;

        while (op_.load()) {
        }
        op_.store(true);

        do {
            head = head_.load(std::memory_order_relaxed);
            size_t tail = tail_.load(std::memory_order_acquire);

            if (head == tail) {
                return false; // Queue is empty
            }
            next_head = (head + 1) % capacity_;

            item = buffer_[head]; // Load the item at the current head
                                  // position
        } while (!head_.compare_exchange_weak(head, next_head,
                                              std::memory_order_release,
                                              std::memory_order_relaxed));

        op_.store(false);
        return true;
    }

    size_t size() const {
        size_t head = head_.load(std::memory_order_acquire);
        size_t tail = tail_.load(std::memory_order_acquire);
        return (capacity_ + tail - head) % capacity_;
    }

    bool empty() const {
        return head_.load(std::memory_order_acquire) ==
               tail_.load(std::memory_order_acquire);
    }

  private:
    const size_t capacity_;
    std::vector<T> buffer_; // The ring buffer
    std::atomic<size_t>
        head_; // Index for the next dequeue (multi-consumer safe)
    std::atomic<size_t>
        tail_; // Index for the next enqueue (multi-producer safe)
    std::atomic<bool> op_;
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