#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

namespace Print {

int cur = 0;
std::mutex mtx;

void print(int i) {
    while (cur < 20) {
        std::unique_lock<std::mutex> lock(mtx);
        if (cur < 20 && cur % 3 == i) {
            std::cout << cur << " ";
            std::cout.flush();
            ++cur;
        }
    }
}

} // namespace Print

namespace Print_Lock_Free {

std::atomic<int> cur(0);
std::atomic<bool> flag(0);

void print(int i) {
    while (true) {
        if (auto val = cur.load(std::memory_order_acquire); val < 20) {
            if (val % 3 == i &&
                flag.exchange(true, std::memory_order_acq_rel) == false) {
                if (cur.compare_exchange_weak(val, val + 1,
                                              std::memory_order_acq_rel)) {
                    std::cout << val << " ";
                    std::cout.flush();
                    // Release the flag
                    flag.store(false, std::memory_order_release);
                }
            }
        } else {
            break;
        }
    }
}
} // namespace Print_Lock_Free

int main() {

    auto start = std::chrono::high_resolution_clock::now();
    std::thread t1(Print::print, 0);
    std::thread t2(Print::print, 1);
    std::thread t3(Print::print, 1);
    std::thread t4(Print::print, 2);
    std::thread t5(Print::print, 2);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nElapsed time: " << elapsed.count() << " s\n";

    std::cout << "\n";
    std::cout.flush();

    start = std::chrono::high_resolution_clock::now();
    std::thread t6(Print_Lock_Free::print, 0);
    std::thread t7(Print_Lock_Free::print, 1);
    std::thread t8(Print_Lock_Free::print, 1);
    std::thread t9(Print_Lock_Free::print, 2);
    std::thread t10(Print_Lock_Free::print, 2);

    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();

    end = std::chrono::high_resolution_clock::now();
    elapsed = end - start;
    std::cout << "\nElapsed time: " << elapsed.count() << " s\n";

    std::cout << "\n";
    std::cout.flush();
    return 0;
}