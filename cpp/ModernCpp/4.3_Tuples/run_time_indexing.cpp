#include <iostream>
#include <string>
#include <tuple>
#include <variant>

template <size_t n, typename... T>
constexpr std::variant<T...> _tuple_index(const std::tuple<T...>& tpl,
                                          size_t i) {
    if constexpr (n >= sizeof...(T)) {
        throw std::out_of_range("tuple index out of range");
    } else if (n == i) {
        // in_place_index 允许在构造 std::variant
        // 时，直接在适当的位置构造所需的替代类型，而不是先构造再赋值。
        return std::variant<T...>{std::in_place_index<n>, std::get<n>(tpl)};
    } else {
        return _tuple_index<n + 1>(tpl, i);
    }
}

template <typename... T>
constexpr std::variant<T...> tuple_index(const std::tuple<T...>& tpl,
                                         size_t i) {
    return _tuple_index<0>(tpl, i);
}

template <typename T0, typename... Ts>
std::ostream& operator<<(std::ostream& os, const std::variant<T0, Ts...>& v) {
    std::visit([&os](auto&& x) { os << x; }, v);
    return os;
}

template <typename T> auto tuple_len(const T& tpl) {
    return std::tuple_size_v<T>;
}

int main() {
    std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
    for (size_t i = 0; i < tuple_len(t); ++i) {
        std::cout << tuple_index(t, i) << " ";
    }
    std::cout << std::endl;

    auto new_tuple =
        std::tuple_cat(std::tuple<std::string>("345"), std::move(t));
    for (size_t i = 0; i < tuple_len(new_tuple); ++i) {
        std::cout << tuple_index(new_tuple, i) << " ";
    }
    std::cout << std::endl;

    auto variant_tuple = tuple_index(new_tuple, 1);
    std::cout << variant_tuple.index() << std::endl;
    std::cout << std::get<1>(variant_tuple) << std::endl;
    return 0;
}