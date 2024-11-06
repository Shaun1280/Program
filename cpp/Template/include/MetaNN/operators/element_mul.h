#ifndef METANN_OPERATORS_ELEMENT_MUL_H
#define METANN_OPERATORS_ELEMENT_MUL_H

#include <MetaNN/data/batch/duplicate.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/matrices/trivial_matrix.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>

namespace MetaNN {

template <typename TP1, typename TP2> struct OperElementMul_ {
    // valid check
  private:
    using rawM1 = std::decay_t<TP1>;
    using rawM2 = std::decay_t<TP2>;

  public:
    static constexpr bool valid =
        (IsMatrix<rawM1> && IsMatrix<rawM2>) ||
        (IsMatrix<rawM1> && IsScalar<rawM2>) ||
        (IsScalar<rawM1> && IsMatrix<rawM2>) ||
        (IsMatrix<rawM1> && IsBatchMatrix<rawM2>) ||
        (IsBatchMatrix<rawM1> && IsMatrix<rawM2>) ||
        (IsBatchMatrix<rawM1> && IsBatchMatrix<rawM2>) ||
        (IsBatchMatrix<rawM1> && IsScalar<rawM2>) ||
        (IsScalar<rawM1> && IsBatchMatrix<rawM2>);

  public:
    template <typename T1, typename T2,
              std::enable_if_t<std::is_same_v<T1, T2>, bool> = true>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        static_assert(
            std::is_same_v<typename rawM1::ElementType,
                           typename rawM2::ElementType>,
            "Matrices with different element types cannot multiply directly");
        static_assert(
            std::is_same_v<typename rawM1::DeviceType,
                           typename rawM2::DeviceType>,
            "Matrices with different device types cannot multiply directly");

        using ResType = BinaryOp<BinaryOpTags::ElementMul, rawM1, rawM2>;
        return ResType(std::forward<TP1>(p_m1), std::forward<TP2>(p_m2));
    }

    template <
        typename T1, typename T2,
        std::enable_if_t<std::is_same_v<CategoryTags::Scalar, T1>, bool> = true,
        std::enable_if_t<std::is_same_v<CategoryTags::Matrix, T2>, bool> = true>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        using ElementType = typename rawM2::ElementType;
        using DeviceType = typename rawM2::DeviceType;
        auto tmpMatrix = MakeTrivalMatrix<ElementType, DeviceType>(
            p_m2.RowNum(), p_m2.ColNum(), std::forward<TP1>(p_m1));

        using ResType = BinaryOp<BinaryOpTags::ElementMul,
                                 RemoveCVRef<decltype(tmpMatrix)>, rawM2>;
        return ResType(std::move(tmpMatrix), std::forward<TP2>(p_m2));
    }

    template <
        typename T1, typename T2,
        std::enable_if_t<std::is_same_v<CategoryTags::Matrix, T1>, bool> = true,
        std::enable_if_t<std::is_same_v<CategoryTags::Scalar, T2>, bool> = true>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        return OperElementMul_<TP2, TP1>::template Eval<T2, T1>(
            std::forward<TP2>(p_m2), std::forward<TP1>(p_m1));
    }

    template <
        typename T1, typename T2,
        std::enable_if_t<std::is_same_v<CategoryTags::Matrix, T1>, bool> = true,
        std::enable_if_t<std::is_same_v<CategoryTags::BatchMatrix, T2>, bool> =
            true>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        static_assert(
            std::is_same_v<typename rawM1::ElementType,
                           typename rawM2::ElementType>,
            "Matrices with different element types cannot multiply directly");
        static_assert(
            std::is_same_v<typename rawM1::DeviceType,
                           typename rawM2::DeviceType>,
            "Matrices with different device types cannot multiply directly");

        Duplicate<rawM1> tmp(std::forward<TP1>(p_m1), p_m2.BatchNum());
        using ResType =
            BinaryOp<BinaryOpTags::ElementMul, Duplicate<rawM1>, rawM2>;
        return ResType(std::move(tmp), std::forward<TP2>(p_m2));
    }

    template <
        typename T1, typename T2,
        std::enable_if_t<std::is_same_v<CategoryTags::BatchMatrix, T1>, bool> =
            true,
        std::enable_if_t<std::is_same_v<CategoryTags::Matrix, T2>, bool> = true>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        return OperElementMul_<TP2, TP1>::template Eval<T2, T1>(
            std::forward<TP2>(p_m2), std::forward<TP1>(p_m1));
    }

    template <
        typename T1, typename T2,
        std::enable_if_t<std::is_same_v<CategoryTags::Scalar, T1>, bool> = true,
        std::enable_if_t<std::is_same_v<CategoryTags::BatchMatrix, T2>, bool> =
            true>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        return OperElementMul_<TP2, TP1>::template Eval<T2, T1>(
            std::forward<TP2>(p_m2), std::forward<TP1>(p_m1));
    }

    template <
        typename T1, typename T2,
        std::enable_if_t<std::is_same_v<CategoryTags::BatchMatrix, T1>, bool> =
            true,
        std::enable_if_t<std::is_same_v<CategoryTags::Scalar, T2>, bool> = true>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        using ElementType = typename rawM1::ElementType;
        using DeviceType = typename rawM1::DeviceType;
        auto tmpMatrix = MakeTrivalMatrix<ElementType, DeviceType>(
            p_m1.RowNum(), p_m1.ColNum(), std::forward<TP2>(p_m2));
        auto tmpBatchMatrix =
            MakeDuplicate(p_m1.BatchNum(), std::move(tmpMatrix));

        using ResType = BinaryOp<BinaryOpTags::ElementMul, rawM1,
                                 RemoveCVRef<decltype(tmpBatchMatrix)>>;
        return ResType(std::forward<TP1>(p_m1), std::move(tmpBatchMatrix));
    }
};

template <typename TP1, typename TP2,
          std::enable_if_t<OperElementMul_<TP1, TP2>::valid, bool> = true>
auto operator*(TP1&& p_m1, TP2&& p_m2) {
    using Cate1 = DataCategory<TP1>;
    using Cate2 = DataCategory<TP2>;

    return OperElementMul_<TP1, TP2>::template Eval<Cate1, Cate2>(
        std::forward<TP1>(p_m1), std::forward<TP2>(p_m2));
}

} // namespace MetaNN

#endif