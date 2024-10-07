#include <atomic>
#include <cassert>
#include <iostream>
#include <thread>
#include <vector>

template <typename T> class SPSCQueue {
  public:
    SPSCQueue(size_t capacity)
        : m_capacity(capacity), m_buffer(capacity), m_head(0), m_tail(0) {
        assert(capacity > 1);
    }

    bool enqueue(const T& item) {
        size_t tail = m_tail.load(std::memory_order_relaxed);
        size_t head = m_head.load(
            std::memory_order_acquire); // (1) Ensures that all subsequent
                                        // memory operations in this thread
                                        // cannot be reordered to before this
                                        // load.

        if ((tail + 1) % m_capacity == head) {
            return false;
        }

        m_buffer[tail] = item;

        // (2) sync with (3)
        m_tail.store((tail + 1) % m_capacity,
                     std::memory_order_release); // (2) Ensures that all memory
                                                 // operations before this store
                                                 // are completed
        return true;
    }

    bool dequeue(T& item) {
        size_t head = m_head.load(std::memory_order_relaxed);
        size_t tail = m_tail.load(std::memory_order_acquire); // (3)

        if (head == tail) {
            return false;
        }

        item = m_buffer[head];

        // (4) sync with (1)
        m_head.store((head + 1) % m_capacity, std::memory_order_release); // (4)
        return true;
    }

  private:
    const size_t m_capacity;
    std::vector<T> m_buffer;
    std::atomic<size_t> m_head;
    std::atomic<size_t> m_tail;
};

int main() {
    SPSCQueue<int> queue(8); // 环形缓冲区的容量为 8

    // 启动生产者线程
    std::thread producer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            while (!queue.enqueue(i)) {
                // busy-wait if the queue is full
            }
            std::cout << "Produced: " + std::to_string(i) + "\n";
        }
    });

    // 启动消费者线程
    std::thread consumer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            int item;
            while (!queue.dequeue(item)) {
                // busy-wait if the queue is empty
            }
            std::cout << "Consumed: " + std::to_string(item) + "\n";
        }
    });

    producer.join();
    consumer.join();
    return 0;
}
