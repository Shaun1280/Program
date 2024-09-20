#include <iostream>

template <typename... T> auto avg(T... args) {
    return 1.0 * (args + ...) / sizeof...(args);
}

template <typename... T> auto sum(T... args) { return (args + ...); }

int main() {
    std::cout << sum(1, 2, 3, 4, 5) << std::endl;
    std::cout << avg(1, 2, 3, 4, 5) << std::endl;
    return 0;
}