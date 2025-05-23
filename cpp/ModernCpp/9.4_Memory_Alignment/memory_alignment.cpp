#include <cstddef>
#include <iostream>

struct Storage {
    char a;
    int b;
    double c;
    long long d;
};

struct alignas(std::max_align_t) AlignasStorage { // align as max long double (16 types)
    char a;
    int b;
    double c;
    long long d;
};

int main() {
    std::cout << alignof(Storage) << std::endl;
    std::cout << alignof(AlignasStorage) << std::endl;
    return 0;
}
