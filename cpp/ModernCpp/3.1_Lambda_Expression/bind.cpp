#include <functional>
#include <iostream>

void foo(int a, int b, int c) { ; }

int main() {
    auto bindFoo = std::bind(foo, std::placeholders::_1, 1, 2);
    bindFoo(3);
    return 0;
}