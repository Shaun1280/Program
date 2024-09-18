#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5};

    if (const auto itr = std::find(vec.begin(), vec.end(), 3);
        itr != vec.end()) {
        std::cout << "Found " << *itr << std::endl;
    } else {
        std::cout << "Not found" << std::endl;
    }

    return 0;
}