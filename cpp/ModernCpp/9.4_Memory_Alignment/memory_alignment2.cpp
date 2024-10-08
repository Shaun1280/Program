#include <cstddef>
#include <iostream>

struct AlignedStruct {
    alignas(2) char a;
    alignas(4) int b; // alignas(8) -> total size = 32
    alignas(8) double c;
    char d;
};

int main() {
    AlignedStruct s;

    std::cout << "Offset of a: " << offsetof(AlignedStruct, a) << std::endl;
    std::cout << "Offset of b: " << offsetof(AlignedStruct, b) << std::endl;
    std::cout << "Offset of c: " << offsetof(AlignedStruct, c) << std::endl;
    std::cout << "Offset of d: " << offsetof(AlignedStruct, d) << std::endl;

    std::cout << "Size of AlignedStruct: " << sizeof(AlignedStruct)
              << std::endl;

    return 0;
}