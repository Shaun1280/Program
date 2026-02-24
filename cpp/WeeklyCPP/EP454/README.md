TODO:
https://www.youtube.com/watch?v=DxFpQa1PyaA

# How `std::invoke` and `std::apply` Are Implemented

Let's look at how these two functions are typically implemented in C++ standard libraries. These implementations are simplified but capture the essential mechanisms.

## `std::invoke` Implementation

```cpp
// Primary template for regular callable objects (functions, lambdas, etc.)
template<typename F, typename... Args>
constexpr auto invoke(F&& f, Args&&... args) 
    -> decltype(std::forward<F>(f)(std::forward<Args>(args)...))
{
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

// Specialization for member function pointers with object references
template<typename R, typename C, typename Obj, typename... Args>
constexpr auto invoke(R (C::*f)(Args...), Obj&& obj, Args&&... args)
    -> decltype((std::forward<Obj>(obj).*f)(std::forward<Args>(args)...))
{
    return (std::forward<Obj>(obj).*f)(std::forward<Args>(args)...);
}

// Specialization for member function pointers with object pointers
template<typename R, typename C, typename Pointer, typename... Args>
constexpr auto invoke(R (C::*f)(Args...), Pointer&& ptr, Args&&... args)
    -> decltype(((*std::forward<Pointer>(ptr)).*f)(std::forward<Args>(args)...))
{
    return ((*std::forward<Pointer>(ptr)).*f)(std::forward<Args>(args)...);
}

// There would also be specializations for const member functions, 
// member data pointers, etc.
```

The key aspects:
1. Uses SFINAE (Substitution Failure Is Not An Error) with `decltype` to select the correct overload
2. Has specialized handling for member function pointers
3. Uses `.*` operator (for object references) and `->*` operator (for pointers)
4. Preserves perfect forwarding with `std::forward`

## `std::apply` Implementation

```cpp
namespace detail {
    template <class F, class Tuple, std::size_t... I>
    constexpr auto apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
        -> decltype(std::invoke(
            std::forward<F>(f), 
            std::get<I>(std::forward<Tuple>(t))...))
    {
        return std::invoke(
            std::forward<F>(f),
            std::get<I>(std::forward<Tuple>(t))...);
    }
}

template <class F, class Tuple>
constexpr auto apply(F&& f, Tuple&& t)
    -> decltype(detail::apply_impl(
        std::forward<F>(f),
        std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{}))
{
    return detail::apply_impl(
        std::forward<F>(f),
        std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{}
    );
}
```

The key aspects:
1. Uses `std::index_sequence` to generate a sequence of indices
2. Unpacks the tuple into individual arguments using parameter pack expansion
3. Calls `std::invoke` internally to handle the actual function invocation
4. Does not have specialized handling for member functions (relies on `std::invoke` for that)

## Key Insights

1. `std::invoke` has specialized handling for member function pointers, which explains why you can pass an object by value/reference (`s`) directly.

2. `std::apply` is implemented using `std::invoke` under the hood, but its job is tuple unpacking, not handling different types of callables.

3. For a member function pointer, you need the object pointer explicitly in the tuple for `std::apply` because it simply unpacks the tuple to `std::invoke` without additional logic.

4. The implementations rely heavily on template metaprogramming features like SFINAE, perfect forwarding, parameter pack expansion, and compile-time index sequences.

This explains why the interface differences exist - `std::invoke` was specifically designed to handle the member function case elegantly, while `std::apply` is just a tuple unpacker that delegates to `std::invoke`.