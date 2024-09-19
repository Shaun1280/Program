#include <vector>

template class std::vector<int>;           // force instantiation
extern template class std::vector<double>; // do not instantiate

int main() {
    std::vector<int> a; // can do this
    // std::vector<double> a; can not do this
    return 0;
}