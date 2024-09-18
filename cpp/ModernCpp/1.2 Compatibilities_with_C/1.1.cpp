#include "foo.h"
#include <functional>
#include <iostream>

int main() {
    [out = std::ref(std::cout << "3 plus 4 is " <<  add(3, 4))]() {
        out.get() << '\n';
    }();
    return 0;
}