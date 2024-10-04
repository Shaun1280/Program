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
    return 0;
}