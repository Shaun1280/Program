#include <functional>
#include <iostream>
#include <map>
#include <string>

template <typename Key, typename Value, typename F>
void update(std::map<Key, Value>& m, F foo) {
    for (auto&& [key, value] : m)
        value = foo(key);
}

int main() {
    std::map<std::string, long long int> m{{"a", 1}, {"b", 2}, {"c", 3}};
    update(m, [](std::string key) -> long long int {
        return std::hash<std::string>{}(key);
    });
    for (auto&& [key, value] : m)
        std::cout << key << ":" << value << std::endl;
}