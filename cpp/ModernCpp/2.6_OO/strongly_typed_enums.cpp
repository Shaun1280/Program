#include <iostream>

enum class new_enum : unsigned int {
    value1,
    value2,
    value3 = 100,
    value4 = 100
};

template <typename T>
std::ostream&
operator<<(std::enable_if_t<std::is_enum_v<T>, std::ostream>& stream,
           const T& e) {
    return stream << static_cast<std::underlying_type_t<T>>(e) << std::endl;
}

int main() {
    std::cout << new_enum::value3 << std::endl;
    return 0;
}