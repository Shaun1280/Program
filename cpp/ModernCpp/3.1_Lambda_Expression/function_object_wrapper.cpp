#include <iostream>

using foo = void(int); // function pointer

void functional(foo f) { f(1); }

int main() {
    auto f = [](int value) { std::cout << value << std::endl; };
    functional(f); // call by function pointer
    f(1);          // call by lambda expression
    return 0;
}