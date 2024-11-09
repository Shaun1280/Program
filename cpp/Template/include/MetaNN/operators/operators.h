#ifndef METANN_OPERATORS_OPERATORS_H
#define METANN_OPERATORS_OPERATORS_H

#include <MetaNN/data/facilities/tags.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/facilities/traits.h>
#include <MetaNN/operators/facilities/category_cal.h>
#include <MetaNN/operators/facilities/oper_seq.h>
#include <MetaNN/operators/facilities/organizer.h>
#include <MetaNN/operators/facilities/tags.h>
#include <MetaNN/operators/facilities/traits.h>

namespace MetaNN {

// TOpTag: Operation Tag; TData: Operand Data (e.g. Matrix<int, CPU>(3, 3))
template <typename TOpTag, typename TData>
class UnaryOp : public OperOrganizer<TOpTag, OperCateCal<TOpTag, TData>> {
    static_assert(std::is_same_v<RemoveCVRef<TData>, TData>,
                  "TData is not available type");
    using Cate = OperCateCal<TOpTag, TData>;

  public:
    using ElementTpype = typename OperElementType_<TOpTag, TData>::type;
    using DeviceType = typename OperDeviceType_<TOpTag, TData>::type;

  public:
    UnaryOp(TData p_data)
        : OperOrganizer<TOpTag, Cate>(p_data), m_data(std::move(p_data)) {}

    [[nodiscard]] bool operator==(const UnaryOp& val) const noexcept {
        return m_data == val.data;
    }

    template <typename TOtherData>
    [[nodiscard]] bool operator==(const TOtherData& val) const noexcept {
        return false;
    }

    template <typename TOtherData>
    [[nodiscard]] bool operator!=(const TOtherData& val) const noexcept {
        return !(operator==(val));
    }

    [[nodiscard]] const TData& Operand() const noexcept { return m_data; }

  private:
    TData m_data;
};

template <typename TOpTag, typename TData1, typename TData2>
class BinaryOp
    : public OperOrganizer<TOpTag, OperCateCal<TOpTag, TData1, TData2>> {
    static_assert(std::is_same_v<RemoveCVRef<TData1>, TData1>,
                  "TData1 is not available type");
    static_assert(std::is_same_v<RemoveCVRef<TData2>, TData2>,
                  "TData2 is not available type");
    using Cate = OperCateCal<TOpTag, TData1, TData2>;

  public:
    using ElementTpype =
        typename OperElementType_<TOpTag, TData1, TData2>::type;
    using DeviceType = typename OperDeviceType_<TOpTag, TData1, TData2>::type;

  public:
    BinaryOp(TData1 data1, TData2 data2)
        : OperOrganizer<TOpTag, Cate>(data1, data2), m_data1(std::move(data1)),
          m_data2(std::move(data2)) {}

    [[nodiscard]] bool operator==(const BinaryOp& val) const noexcept {
        return (m_data1 == val.m_data1) && (m_data2 == val.m_data2);
    }

    template <typename TOtherData>
    [[nodiscard]] bool operator==(const TOtherData& val) const noexcept {
        return false;
    }

    template <typename TOtherData>
    [[nodiscard]] bool operator!=(const TOtherData& val) const noexcept {
        return !(operator==(val));
    }

    [[nodiscard]] const TData1& Operand1() const noexcept { return m_data1; }

    [[nodiscard]] const TData2& Operand2() const noexcept { return m_data2; }

  private:
    TData1 m_data1;
    TData2 m_data2;

    // using TPrincipal = PrincipalDataType<Cate, ElementType, DeviceType>;
    // EvalBuffer<TPrincipal> m_evalBuf;
};

template <typename TOpTag, typename TData1, typename TData2, typename TData3>
class TernaryOp
    : public OperOrganizer_<TOpTag,
                            OperCateCal<TOpTag, TData1, TData2, TData3>> {
    static_assert(std::is_same_v<RemoveCVRef<TData1>, TData1>,
                  "TData1 is not an available type");
    static_assert(std::is_same_v<RemoveCVRef<TData2>, TData2>,
                  "TData2 is not an available type");
    static_assert(std::is_same_v<RemoveCVRef<TData3>, TData3>,
                  "TData3 is not an available type");
    using Cate = OperCateCal<TOpTag, TData1, TData2, TData3>;

  public:
    using ElementTpype =
        typename OperElementType_<TOpTag, TData1, TData2, TData3>::type;
    using DeviceType =
        typename OperDeviceType_<TOpTag, TData1, TData2, TData3>::type;

  public:
    TernaryOp(TData1 data1, TData2 data2, TData3 data3)
        : OperOrganizer_<TOpTag, Cate>(data1, data2, data3),
          m_data1(std::move(data1)), m_data2(std::move(data2)),
          m_data3(std::move(data3)) {}

    [[nodiscard]] bool operator==(const TernaryOp& val) const noexcept {
        return (m_data1 == val.m_data1) && (m_data2 == val.m_data2) &&
               (m_data3 == val.m_data3);
    }

    template <typename TOtherData>
    [[nodiscard]] bool operator==(const TOtherData& val) const noexcept {
        return false;
    }

    template <typename TOtherData>
    [[nodiscard]] bool operator!=(const TOtherData& val) const noexcept {
        return !(operator==(val));
    }

    [[nodiscard]] const TData1& Operand1() const noexcept { return m_data1; }

    [[nodiscard]] const TData2& Operand2() const noexcept { return m_data2; }

    [[nodiscard]] const TData3& Operand3() const noexcept { return m_data3; }

  private:
    TData1 m_data1;
    TData2 m_data2;
    TData3 m_data3;
}

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