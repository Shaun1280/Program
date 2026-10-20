#include <concepts>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>

namespace
{
template <typename Tuple, typename... Args>
struct is_tail_constructible;

template <typename... Elements, typename... Args>
struct is_tail_constructible<std::tuple<Elements...>, Args...>
    : std::bool_constant<( sizeof...( Elements ) == sizeof...( Args ) ) &&
                         ( std::constructible_from<Elements, Args> && ... )> // unary right fold expression
{
};

template <typename Tuple, typename... Args>
constexpr bool is_tail_constructible_v = is_tail_constructible<Tuple, Args...>::value;
} // namespace

class tuple_elems_func_args_match
{
private:
    std::set<std::tuple<std::string, std::string, std::string, std::string, int>> _set;

public:
    using key_type = decltype( _set )::key_type;

    template <typename... Keys>
        requires is_tail_constructible_v<key_type, const char*, Keys...>
    bool is_inserted( const char* topic, Keys&&... keys )
    {
        return !_set.emplace( topic, std::forward<Keys>( keys )... ).second;
    }
};