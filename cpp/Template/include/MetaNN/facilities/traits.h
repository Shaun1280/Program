#ifndef METANN_FACILITIES_TRAITS_H
#define METANN_FACILITIES_TRAITS_H

#include <type_traits>

namespace MetaNN {

// Or
template <bool cur, typename TNext> constexpr static bool OrValue = true;

template <typename TNext>
constexpr static bool OrValue<false, TNext> = TNext::value;

// And
template <bool cur, typename TNext> constexpr static bool AndValue = false;

template <typename TNext>
constexpr static bool AndValue<true, TNext> = TNext::value;

template <typename T>
using RemoveCVRef = std::remove_cv_t<std::remove_reference_t<T>>;

} // namespace MetaNN

#endif // METANN_FACILITIES_TRAITS_H