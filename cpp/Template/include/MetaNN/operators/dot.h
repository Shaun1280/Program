#ifndef METANN_OPERATORS_DOT_H
#define METANN_OPERATORS_DOT_H

#include <MetaNN/data/batch/duplicate.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/matrices/trivial_matrix.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>
#include <MetaNN/operators/operators.h>

namespace MetaNN {

template <> class OperOrganizer<BinaryOpTags::Dot, CategoryTags::Matrix> {
  public:
    template <typename TD1, typename TD2>
    OperOrganizer(const TD1& data1, const TD2& data2)
        : m_rowNum(data1.RowNum()), m_colNum(data2.ColNum()) {
        assert(data1.ColNum() == data2.RowNum());
    }

    [[nodiscard]] size_t RowNum() const noexcept { return m_rowNum; }
    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }

  private:
    size_t m_rowNum;
    size_t m_colNum;
};

template <> class OperOrganizer<BinaryOpTags::Dot, CategoryTags::BatchMatrix> {
  public:
    template <typename TD1, typename TD2>
    OperOrganizer(const TD1& data1, const TD2& data2)
        : m_rowNum(data1.RowNum()), m_colNum(data2.ColNum()),
          m_batchNum(data1.BatchNum()) {
        assert(data1.ColNum() == data2.RowNum());
        assert(data1.BatchNum() == data2.BatchNum());
    }

    [[nodiscard]] size_t RowNum() const noexcept { return m_rowNum; }
    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }
    [[nodiscard]] size_t BatchNum() const noexcept { return m_batchNum; }

  private:
    size_t m_rowNum;
    size_t m_colNum;
    size_t m_batchNum;
};

template <typename TP1, typename TP2> struct OperDot_ {
    // valid check
  private:
    using rawM1 = std::decay_t<TP1>;
    using rawM2 = std::decay_t<TP2>;

  public:
    static constexpr bool valid =
        (IsMatrix<rawM1> && IsMatrix<rawM2>) ||
        (IsBatchMatrix<rawM1> && IsMatrix<rawM2>) ||
        (IsMatrix<rawM1> && IsBatchMatrix<rawM2>) ||
        (IsBatchMatrix<rawM1> && IsBatchMatrix<rawM2>);

  public:
    template <typename T1, typename T2,
              std::enable_if_t<std::is_same_v<T1, T2>, bool> = true>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        static_assert(
            std::is_same_v<typename rawM1::ElementType,
                           typename rawM2::ElementType>,
            "Matrices with different element types cannot dot directly");
        static_assert(
            std::is_same_v<typename rawM1::DeviceType,
                           typename rawM2::DeviceType>,
            "Matrices with different device types cannot dot directly");

        using ResType = BinaryOp<BinaryOpTags::Dot, rawM1, rawM2>;
        return ResType(std::forward<TP1>(p_m1), std::forward<TP2>(p_m2));
    }

    template <
        typename T1, typename T2,
        std::enable_if_t<std::is_same_v<CategoryTags::BatchMatrix, T1>, bool> =
            true,
        std::enable_if_t<std::is_same_v<CategoryTags::Matrix, T2>, bool> = true>
    static auto Eval(TP1&& p_m1, TP2&& p_m2) {
        static_assert(
            std::is_same_v<typename rawM1::ElementType,
                           typename rawM2::ElementType>,
            "Matrices with different element types cannot dot directly");
        static_assert(
            std::is_same_v<typename rawM1::DeviceType,
                           typename rawM2::DeviceType>,
            "Matrices with different device types cannot dot directly");

        Duplicate<rawM2> tmp(std::forward<TP2>(p_m2), p_m1.BatchNum());
        using ResType = BinaryOp<BinaryOpTags::Dot, rawM1, Duplicate<rawM2>>;
        return ResType(std::forward<TP1>(p_m1), std::move(tmp));
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
            "Matrices with different element types cannot dot directly");
        static_assert(
            std::is_same_v<typename rawM1::DeviceType,
                           typename rawM2::DeviceType>,
            "Matrices with different device types cannot dot directly");

        Duplicate<rawM1> tmp(std::forward<TP1>(p_m1), p_m2.BatchNum());
        using ResType = BinaryOp<BinaryOpTags::Dot, Duplicate<rawM1>, rawM2>;
        return ResType(std::move(tmp), std::forward<TP2>(p_m2));
    }
};

template <typename TP1, typename TP2,
          std::enable_if_t<OperDot_<TP1, TP2>::valid, bool> = true>
auto Dot(TP1&& p_m1, TP2&& p_m2) {
    using Cate1 = DataCategory<TP1>;
    using Cate2 = DataCategory<TP2>;

    return OperDot_<TP1, TP2>::template Eval<Cate1, Cate2>(
        std::forward<TP1>(p_m1), std::forward<TP2>(p_m2));
}

} // namespace MetaNN

#endif