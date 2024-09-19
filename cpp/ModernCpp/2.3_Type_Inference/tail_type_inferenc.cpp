#include <iostream>
#include <type_traits>

template <typename R, typename T, typename U> R add(T x, U y) { return x + y; }

// cpp11
template <typename T, typename U> auto add2(T x, U y) -> decltype(x + y) {
    return x + y;
}

// c++14
template <typename T, typename U> decltype(auto) add3(T x, U y) {
    return x + y;
}

std::string lookup1() { return "lookup1"; }
std::string &lookup2() {
    static std::string s = "lookup2";
    return s;
}

decltype(auto) lookup3() {
    if constexpr (true) {
        return lookup1();
    } else {
        return lookup2();
    }
}

int main() {
    auto w = add2<int, double>(1, 2.0);
    if (std::is_same_v<decltype(w), double>) {
        std::cout << "w is double: ";
    }
    std::cout << w << std::endl;

    auto w2 = add3<int, double>(1, 2.0);
    if (std::is_same_v<decltype(w), double>) {
        std::cout << "w2 is double: ";
    }
    std::cout << w2 << std::endl;

    auto s = lookup3();
    std::cout << s << std::endl;
}
