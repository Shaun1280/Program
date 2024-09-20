#include <functional>
#include <iostream>

int foo(int para) { return para; }

int main() {
    std::function<int(int)> f(foo);
    auto f2 = foo;

    int important = 1;
    std::function<int(int)> f3 = [&important](int para) {
        return 1 + para + important;
    };

    std::cout << f(1) << std::endl;
    std::cout << f2(1) << std::endl;
    std::cout << f3(1) << std::endl;
}