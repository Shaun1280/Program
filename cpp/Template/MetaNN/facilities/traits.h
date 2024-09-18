#pragma once

#include <stddef.h>

namespace MetaNN {

template <typename T>
using RemoveCVRef = std::remove_cv_t<std::remove_reference_t<T>>;

} // namespace MetaNN