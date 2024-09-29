#ifndef METANN_DATA_FACILITIES_LOWER_ACCESS_H
#define METANN_DATA_FACILITIES_LOWER_ACCESS_H

#include <MetaNN/facilities/traits.h>

namespace MetaNN {

// lower access declaration
template <typename TData> struct LowerAccessImpl;

// Interface for lower access
template <typename TData> auto LowerAccess(TData&& data) {
    using RawType = RemoveCVRef<TData>;
    return LowerAccessImpl<RawType>(std::forward<TData>(data));
}

} // namespace MetaNN

#endif // METANN_DATA_FACILITIES_LOWER_ACCESS_H