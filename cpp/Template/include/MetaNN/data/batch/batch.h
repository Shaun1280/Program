#ifndef METANN_DATA_BATCH_BATCH_H
#define METANN_DATA_BATCH_BATCH_H

#include <MetaNN/data/facilities/tags.h>
#include <MetaNN/data/facilities/traits.h>

namespace MetaNN {

template <typename TElement, typename TDevice, typename TCategory> class Batch;

template <typename TElement, typename TDevice>
constexpr bool IsBatchMatrix<Batch<TElement, TDevice, CategoryTags::Matrix>> =
    true;

template <typename TElement, typename TDevice>
constexpr bool IsBatchScalar<Batch<TElement, TDevice, CategoryTags::Scalar>> =
    true;

} // namespace MetaNN

#endif // MetaNN_DATA_BATCH_BATCH_H