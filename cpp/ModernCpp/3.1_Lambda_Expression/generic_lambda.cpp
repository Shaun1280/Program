#include <iostream>

void generic_lambda() {
    auto generic = [](auto x, auto y) { return x + y; };
    std::cout << generic(1, 2) << std::endl;
}

int main() {
    generic_lambda();
    return 0;
}