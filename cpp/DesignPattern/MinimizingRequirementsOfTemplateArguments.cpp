#include <concepts>
#include <iterator>

template <typename InputIt, typename OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
    return d_first;
}

template <
    std::input_iterator InputIt,
    std::output_iterator<typename std::iterator_traits<InputIt>::value_type>
        OutputIt>
OutputIt copy2(InputIt first, InputIt last, OutputIt d_first) {
    return d_first;
}

int main() { return 0; }