#pragma once

#include <concepts>
#include <functional>
#include <type_traits>
#include <utility>

/*
 * Two unique_ptr<T, D1> and unique_ptr<T, D2> with different deleter types are incompatible types.
 *
 */
template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr
{

};