#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

int main() {
    // initialize as nullptr to prevent consumer load a dangling pointer
    std::atomic<int*> ptr(nullptr);
    int v;
    std::thread producer([&]() {
        int* p = new int(42);
        v = 1024;
        ptr.store(p, std::memory_order_release);
    });
    std::thread consumer([&]() {
        int* p;
        while (!(p = ptr.load(std::memory_order_consume)))
            ;
        // Due to the release-consume ordering, when the consumer sees the new
        // value of ptr, it's guaranteed to also see the correct value of v
        // (1024).
        std::cout << "p: " << *p << std::endl;
        std::cout << "v: " << v << std::endl;
    });
    producer.join();
    consumer.join();

    return 0;
}
