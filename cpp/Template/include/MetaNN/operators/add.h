#ifndef METANN_OPERATORS_ADD_H
#define METANN_OPERATORS_ADD_H

#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>

namespace MetaNN {

template <typename TP1, typename TP2> struct OperAdd_ {
    // valid check
  private:
    using rawM1 = RemoveCVRef<TP1>;
    using rawM2 = RemoveCVRef<TP2>;

  public:
    static constexpr bool valid =
        (IsMatrix<rawM1> && IsMatrix<rawM2>) ||
        (IsMatrix<rawM1> && IsScalar<rawM2>) ||
        (IsScalar<rawM1> && IsMatrix<rawM2>) ||
        (IsBatchMatrix<rawM1> && IsMatrix<rawM2>) ||
        (IsMatrix<rawM1> && IsBatchMatrix<rawM2>) ||
        (IsBatchMatrix<rawM1> && IsBatchMatrix<rawM2>) ||
        (IsBatchMatrix<rawM1> && IsScalar<rawM2>) ||
        (IsScalar<rawM1> && IsBatchMatrix<rawM2>);

  public:
    template <typename T1, typename T2,
              std::enable_if_t<std::is_same<T1, T2>::value>* = nullptr>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        static_assert(
            std::is_same<typename rawM1::ElementType,
                         typename rawM2::ElementType>::value,
            "Matrices with different element types cannot add directly");
        static_assert(
            std::is_same<typename rawM1::DeviceType,
                         typename rawM2::DeviceType>::value,
            "Matrices with different device types cannot add directly");

        using ResType = BinaryOp<BinaryOpTags::Add, rawM1, rawM2>;
        return ResType(std::forward<TP1>(p_m1), std::forward<TP2>(p_m2));
    }

    template <typename T1, typename T2,
              std::enable_if_t<std::is_same<CategoryTags::Scalar, T1>::value>* =
                  nullptr,
              std::enable_if_t<std::is_same<CategoryTags::Matrix, T2>::value>* =
                  nullptr>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        using ElementType = typename rawM2::ElementType;
        using DeviceType = typename rawM2::DeviceType;
        auto tmpMatrix = MakeTrivalMatrix<ElementType, DeviceType>(
            p_m2.RowNum(), p_m2.ColNum(), std::forward<TP1>(p_m1));

        using ResType = BinaryOp<BinaryOpTags::Add,
                                 RemConstRef<decltype(tmpMatrix)>, rawM2>;
        return ResType(std::move(tmpMatrix), std::forward<TP2>(p_m2));
    }

    template <typename T1, typename T2,
              std::enable_if_t<std::is_same<CategoryTags::Matrix, T1>::value>* =
                  nullptr,
              std::enable_if_t<std::is_same<CategoryTags::Scalar, T2>::value>* =
                  nullptr>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        return OperAdd_<TP2, TP1>::template Eval<T2, T1>(
            std::forward<TP2>(p_m2), std::forward<TP1>(p_m1));
    }

    template <typename T1, typename T2,
              std::enable_if_t<std::is_same<CategoryTags::BatchMatrix,
                                            T1>::value>* = nullptr,
              std::enable_if_t<std::is_same<CategoryTags::Matrix, T2>::value>* =
                  nullptr>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        static_assert(
            std::is_same<typename rawM1::ElementType,
                         typename rawM2::ElementType>::value,
            "Matrices with different element types cannot add directly");
        static_assert(
            std::is_same<typename rawM1::DeviceType,
                         typename rawM2::DeviceType>::value,
            "Matrices with different device types cannot add directly");

        Duplicate<rawM2> tmp(std::forward<TP2>(p_m2), p_m1.BatchNum());

        using ResType = BinaryOp<BinaryOpTags::Add, rawM1, Duplicate<rawM2>>;
        return ResType(std::forward<TP1>(p_m1), std::move(tmp));
    }

    template <typename T1, typename T2,
              std::enable_if_t<std::is_same<CategoryTags::Matrix, T1>::value>* =
                  nullptr,
              std::enable_if_t<std::is_same<CategoryTags::BatchMatrix,
                                            T2>::value>* = nullptr>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        return OperAdd_<TP2, TP1>::template Eval<T2, T1>(
            std::forward<TP2>(p_m2), std::forward<TP1>(p_m1));
    }

    template <typename T1, typename T2,
              std::enable_if_t<std::is_same<CategoryTags::Scalar, T1>::value>* =
                  nullptr,
              std::enable_if_t<std::is_same<CategoryTags::BatchMatrix,
                                            T2>::value>* = nullptr>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        using ElementType = typename rawM2::ElementType;
        using DeviceType = typename rawM2::DeviceType;
        auto tmpMatrix = MakeTrivalMatrix<ElementType, DeviceType>(
            p_m2.RowNum(), p_m2.ColNum(), std::forward<TP1>(p_m1));

        auto tmpBatchMatrix =
            MakeDuplicate(p_m2.BatchNum(), std::move(tmpMatrix));

        using ResType = BinaryOp<BinaryOpTags::Add,
                                 RemConstRef<decltype(tmpBatchMatrix)>, rawM2>;
        return ResType(std::move(tmpBatchMatrix), std::forward<TP2>(p_m2));
    }

    template <typename T1, typename T2,
              std::enable_if_t<std::is_same<CategoryTags::BatchMatrix,
                                            T1>::value>* = nullptr,
              std::enable_if_t<std::is_same<CategoryTags::Scalar, T2>::value>* =
                  nullptr>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        return OperAdd_<TP2, TP1>::template Eval<T2, T1>(
            std::forward<TP2>(p_m2), std::forward<TP1>(p_m1));
    }
};

template <typename TP1, typename TP2,
          std::enable_if_t<OperAdd_<TP1, TP2>::valid, bool> = true>
auto operator+(TP1&& p_m1, TP2&& p_m2) {
    using Cate1 = DataCategory<TP1>;
    using Cate2 = DataCategory<TP2>;

    return OperAdd_<TP1, TP2>::template Eval<Cate1, Cate2>(
        std::forward<TP1>(p_m1), std::forward<TP2>(p_m2));
}

} // namespace MetaNN

#endif