#ifndef METANN_OPERATORS_OPERATORS_H
#define METANN_OPERATORS_OPERATORS_H

#include <MetaNN/data/facilities/tags.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/operators/facilities/category_cal.h>
#include <MetaNN/operators/facilities/oper_seq.h>
#include <MetaNN/operators/facilities/organizer.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>

namespace MetaNN {

template <typename TOpTag, typename TData> class UnaryOp;

template <typename TOpTag, typename TData1, typename TData2> class BinaryOp;

template <typename TOpTag, typename TData1, typename TData2, typename TData3>
class TernaryOp;

template <typename TOpTag, typename TData>
static constexpr bool IsMatrix<UnaryOp<TOpTag, TData>> =
    std::is_same_v<OperCateCal<TOpTag, TData>, CategoryTags::Matrix>;

template <typename TOpTag, typename TData>
constexpr bool IsScalar<UnaryOp<TOpTag, TData>> =
    std::is_same_v<OperCateCal<TOpTag, TData>, CategoryTags::Scalar>;

template <typename TOpTag, typename TData>
static constexpr bool IsBatchMatrix<UnaryOp<TOpTag, TData>> =
    std::is_same_v<OperCateCal<TOpTag, TData>, CategoryTags::BatchMatrix>;

template <typename TOpTag, typename TData>
static constexpr bool IsBatchScalar<UnaryOp<TOpTag, TData>> =
    std::is_same_v<OperCateCal<TOpTag, TData>, CategoryTags::BatchScalar>;

template <typename TOpTag, typename TData1, typename TData2>
static constexpr bool IsScalar<BinaryOp<TOpTag, TData1, TData2>> =
    std::is_same_v<OperCateCal<TOpTag, TData1, TData2>, CategoryTags::Scalar>;

template <typename TOpTag, typename TData1, typename TData2>
static constexpr bool IsMatrix<BinaryOp<TOpTag, TData1, TData2>> =
    std::is_same_v<OperCateCal<TOpTag, TData1, TData2>, CategoryTags::Matrix>;

template <typename TOpTag, typename TData1, typename TData2>
static constexpr bool IsBatchMatrix<BinaryOp<TOpTag, TData1, TData2>> =
    std::is_same_v<OperCateCal<TOpTag, TData1, TData2>,
                   CategoryTags::BatchMatrix>;

template <typename TOpTag, typename TData1, typename TData2>
static constexpr bool IsBatchScalar<BinaryOp<TOpTag, TData1, TData2>> =
    std::is_same_v<OperCateCal<TOpTag, TData1, TData2>,
                   CategoryTags::BatchScalar>;

template <typename TOpTag, typename TData1, typename TData2, typename TData3>
static constexpr bool IsScalar<TernaryOp<TOpTag, TData1, TData2, TData3>> =
    std::is_same_v<OperCateCal<TOpTag, TData1, TData2, TData3>,
                   CategoryTags::Scalar>;

template <typename TOpTag, typename TData1, typename TData2, typename TData3>
static constexpr bool IsMatrix<TernaryOp<TOpTag, TData1, TData2, TData3>> =
    std::is_same_v<OperCateCal<TOpTag, TData1, TData2, TData3>,
                   CategoryTags::Matrix>;

template <typename TOpTag, typename TData1, typename TData2, typename TData3>
static constexpr bool IsBatchMatrix<TernaryOp<TOpTag, TData1, TData2, TData3>> =
    std::is_same_v<OperCateCal<TOpTag, TData1, TData2, TData3>,
                   CategoryTags::BatchMatrix>;

template <typename TOpTag, typename TData1, typename TData2, typename TData3>
static constexpr bool IsBatchScalar<TernaryOp<TOpTag, TData1, TData2, TData3>> =
    std::is_same_v<OperCateCal<TOpTag, TData1, TData2, TData3>,
                   CategoryTags::BatchScalar>;

} // namespace MetaNN

#endif // METANN_OPERATORS_OPERATORS_H