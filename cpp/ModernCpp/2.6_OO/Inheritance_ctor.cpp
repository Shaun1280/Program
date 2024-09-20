#include <iostream>
#include <memory>

class Base {
  public:
    int value1;
    int value2;
    Base() { value1 = 1; }
    Base(int value) : Base() { // delegate Base() constructor
        value2 = value;
    }
};

class Subclass : public Base {
  public:
    using Base::Base; // inheritance constructor
};

// Without the inheritance constructor, you'd need to write:
class Subclass2 : public Base {
  public:
    Subclass2() : Base() {}
    Subclass2(int value) : Base(value) {}
};

int main() {
    Subclass s(3);
    std::cout << s.value1 << std::endl;
    std::cout << s.value2 << std::endl;

    return 0;
}
