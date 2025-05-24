#include <iostream>
#include <type_traits>
#include <utility>

template <typename T>
constexpr decltype(auto) move(T&& param) {
    using ReturnType = std::remove_reference_t<T>&&;
    return static_cast<ReturnType>(param);
}

template <typename T>
constexpr T&& forward(std::remove_reference_t<T>& param) {
    return static_cast<T&&>(param);
}

template <typename T>
constexpr T&& forward(std::remove_reference_t<T>&& param) {
    static_assert(
        !std::is_lvalue_reference_v<T>,
        "template argument substituting T is an lvalue reference type");
    return static_cast<T&&>(param);
}

void reference(int& v) { std::cout << "lvalue reference" << std::endl; }
void reference(int&& v) { std::cout << "rvalue reference" << std::endl; }

template <typename T>
void pass(T&& v) {
    std::cout << "          normal param passing: ";
    reference(v);
    std::cout << "       std::move param passing: ";
    reference(move(v));
    std::cout << "    std::forward param passing: ";
    reference(forward<T>(v));
    std::cout << "static_cast<T&&> param passing: ";
    reference(static_cast<T&&>(v));
}

int main() {
    std::cout << "rvalue pass:" << std::endl;
    pass(1);

    std::cout << "lvalue pass:" << std::endl;
    int l = 1;
    pass(l);

    return 0;
}