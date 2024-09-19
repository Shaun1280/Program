#include <iostream>

// C++17
template <auto N> void foo() { std::cout << N << std::endl; }

int main() {
    foo<42>();
    return 0;
}