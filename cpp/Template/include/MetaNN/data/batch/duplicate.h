#ifndef METANN_DATA_BATCH_DUPLICATE_H
#define METANN_DATA_BATCH_DUPLICATE_H

#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/facilities/traits.h>
#include <cassert>
#include <memory>
#include <vector>

namespace MetaNN {

template <typename TData, typename TDataCate> class DuplicateImpl;

template <typename TData>
class Duplicate : public DuplicateImpl<TData, DataCategory<TData>> {
  public:
    using ElementType = typename TData::ElementType;
    using DeviceType = typename TData::DeviceType;

    // inheritance constructor
    using DuplicateImpl<TData, DataCategory<TData>>::DuplicateImpl;
};

// If element type is matrix, then the duplicate is batch matrix
template <typename TData>
static constexpr bool IsBatchMatrix<Duplicate<TData>> = IsMatrix<TData>;

// If element type is scalar, then the duplicate is batch scalar
template <typename TData>
static constexpr bool IsBatchScalar<Duplicate<TData>> = IsScalar<TData>;

} // namespace MetaNN

#endif // METANN_DATA_BATCH_DUPLICATE_H
