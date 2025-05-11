#include <iostream>
#include <utility>  // For std::swap

namespace custom {

class CustomType {
    int* data;
    size_t size;

   public:
    // Constructor
    CustomType(size_t s = 10) : size(s), data(new int[s]) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = i;
        }
    }

    // Copy constructor
    CustomType(const CustomType& other)
        : size(other.size), data(new int[other.size]) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Destructor
    ~CustomType() { delete[] data; }

    // Print method for demonstration
    void print() const {
        std::cout << "CustomType [";
        for (size_t i = 0; i < size; ++i) {
            if (i != 0) std::cout << ", ";
            std::cout << data[i];
        }
        std::cout << "]\n";
    }

    // Friend declaration for swap
    friend void swap(CustomType& first, CustomType& second);
};

void swap(CustomType& first, CustomType& second) {
    using std::swap;
    swap(first.size, second.size);
    swap(first.data, second.data);
}
}  // namespace custom

template <typename T>
void some_function(T& value) {
    std::cout << "Before swap: \n";

    if constexpr (std::is_same_v<T, custom::CustomType>) {
        value.print();
    } else {
        std::cout << value << "\n";
    }

    T tmp(10);

    using std::swap;   // Bring std::swap into scope
    swap(tmp, value);  // Unqualified call to swap (uses ADL)
    // In comparision, std::, custom:: are qualified calls

    std::cout << "After swap:\n";
    if constexpr (std::is_same_v<T, custom::CustomType>) {
        value.print();
    } else {
        std::cout << "Value: " << value << "\n";
    }
}

int main() {
    // Demonstration with CustomType
    custom::CustomType ct1(5);
    std::cout << "Testing with CustomType:\n";
    some_function(ct1);

    // Demonstration with int
    int x = 42;
    std::cout << "\nTesting with int:\n";
    some_function(x);
    return 0;
}