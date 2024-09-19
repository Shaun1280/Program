#ifndef METANN_FACILITIES_TRAITS_H
#define METANN_FACILITIES_TRAITS_H

#include <type_traits>

namespace MetaNN {

template <typename T>
using RemoveCVRef = std::remove_cv_t<std::remove_reference_t<T>>;

} // namespace MetaNN

#endif // METANN_FACILITIES_TRAITS_H