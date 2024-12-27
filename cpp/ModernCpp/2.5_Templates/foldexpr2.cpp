#include <iostream>
#include <utility>
#include <limits>
#include <vector>

template <typename T>
T sum_recursive(T&& first) {
    return first;
}

template <typename T, typename... Args>
T sum_recursive(T first, Args&&... args) {
    return first + sum_recursive(args...);
}

template <typename... Args>
auto sum_unary_left_fold(Args... args) {
    // unary left fold expression (... op pack)
    // expands to: ((1 + 2) + 3) + 4 ...
    return (... + args);
}

template <typename... Args>
auto sum_unary_right_fold(Args... args) {
    // unary right fold expression （pack op ...)
    // expands to: 1 + (2 + (3 + 4)) ...
    return (args + ...);
}

template <typename... Args>
auto sum_binary_left_fold(Args... args) {
    // binary left fold expression (init op ... op pack)
    // expands to: (((100 + 4) + 3) + 2) + 1 ...
    return (100 + ... + args);
}

template <typename... Args>
auto sum_binary_right_fold(Args... args) {
    // binary right fold expression (pack op ... op init)
    // expands to 1 + (2 + (3 + (4 + 100))) ...
    return (args + ... + 100);
}

template <typename... Args>
void print_binary_left_fold(Args... args) {
    // binary left fold expression (init op ... op pack)
    // expands to: ((std::cout << 1) << 2) << 3 ...
    (std::cout << ... << args);
    std::cout << std::endl;
}

template <typename... Args>
void print_unary_left_fold(Args... args) {
    // unary left fold expression
    // expands to: ((std::cout << 1 << " "), (std::cout << "hello" << " ")), (std::cout << 3.14 << " ")
    (..., (std::cout << args << " "));
    std::cout << std::endl;
}

template <typename... Args>
void print_unary_right_fold(Args... args) {
    // unary right fold expression
    // expands to: (std::cout << 1 << " "), ((std::cout << "hello" << " "), (std::cout << 3.14 << " "))
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}

template <typename... Ts>
void print_limits() {
    ((std::cout << +std::numeric_limits<Ts>::max() << " "), ...);
    std::cout << std::endl;
}

template <typename T, typename... Args>
void vector_extend(std::vector<T>& vec, Args&&... args) {
    // unary right fold expression
    // expands to: std::is_constructible_v<T, Arg1&&> && (std::is_constructible_v<T, Arg2&&> && std::is_constructible_v<T, Arg3&&>)
    static_assert((std::is_constructible_v<T, Args&&> && ...));
    // unary right fold expression
    // expands to: vec.push_back(std::forward<Arg1>(arg1)), (vec.push_back(std::forward<Arg2>(arg2)), vec.push_back(std::forward<Arg3>(arg3)))
    (vec.push_back(std::forward<Args>(args)), ...);
}

int main() {
    std::cout << sum_recursive(1, 2, 3, 4, 5) << std::endl;
    std::cout << sum_unary_left_fold(1, 2, 3, 4, 5) << std::endl;
    std::cout << sum_unary_right_fold(1, 2, 3, 4, 5) << std::endl;
    std::cout << sum_binary_left_fold(1, 2, 3, 4, 5) << std::endl;
    std::cout << sum_binary_right_fold(1, 2, 3, 4, 5) << std::endl;
    print_binary_left_fold(1, 2, 3, 4, 5);
    print_unary_left_fold(1, 2, 3, 4, 5);
    print_unary_right_fold(1, 2, 3, 4, 5);
    print_limits<char, int, long>();

    std::vector<int> v;
    vector_extend(v, 1.0, 2.0, 3, 4, -1);
    for (const auto& x : v) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}
