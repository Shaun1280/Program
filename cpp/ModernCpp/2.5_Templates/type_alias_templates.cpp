#include <iostream>
#include <string>
#include <vector>

template <typename T, typename U> class MagicType {
  public:
    T dark;
    U magic;
};

typedef int (*Process)(void*);
using NewProcess = int (*)(void*);

template <typename T>
using TrueDarkMagic = MagicType<std::vector<T>, std::string>;

TrueDarkMagic<int>
    magic; // magic.dark is a vector<int> and magic.magic is a string

template <typename T0, typename... T> void printf2(T0 t0, T... t) {
    std::cout << t0 << std::endl;
    if constexpr (sizeof...(t) > 0) {
        printf2(t...);
    }
}

template <typename T, typename... Ts> auto printf3(T value, Ts... args) {
    std::cout << value << std::endl;
    // value is needed as return value of type T
    // since initializer_list contains objects of type T
    (void)std::initializer_list<T>{
        ([&args] { std::cout << args << std::endl; }(), value)...};
}

template <typename... T> auto sum(T... args) { return (args + ...); }

int main() {
    printf2(1, 2, 3, 4, 5);
    printf3(1, 2, 3, 4, 5);
    std::cout << sum(1, 2, 3, 4, 5) << std::endl;
    return 0;
}