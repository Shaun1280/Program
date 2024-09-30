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

template <typename TData> class DuplicateImpl<TData, CategoryTags::Matrix> {
    static_assert(std::is_same_v<RemoveCVRef<TData>, TData>,
                  "Unavailable data type");

  public:
    using ElementType = typename TData::ElementType;
    using DeviceType = typename TData::DeviceType;

  public:
    DuplicateImpl(TData data, size_t batch_num)
        : m_data(std::move(data)), m_batchNum(batch_num) {
        assert(m_batchNum != 0);
    }

  public:
    [[nodiscard]] size_t RowNum() const noexcept { return m_data.RowNum(); }
    [[nodiscard]] size_t ColNum() const noexcept { return m_data.ColNum(); }

    [[nodiscard]] size_t BatchNum() const noexcept { return m_batchNum; }

    [[nodiscard]] const TData& Element() const noexcept { return m_data; }

    [[nodiscard]] bool operator==(const Duplicate<TData>& val) const noexcept {
        decltype(auto) tmp =
            static_cast<const DuplicateImpl<TData, CategoryTags::Matrix>&>(val);
        return (tmp.m_data == m_data) && (tmp.m_batchNum == m_batchNum);
    }

    template <typename TOtherType>
    [[nodiscard]] bool operator==(const TOtherType&) const noexcept {
        return false;
    }

    template <typename TCompData>
    [[nodiscard]] bool operator!=(const TCompData& val) const noexcept {
        return !(operator==(val));
    }

  protected:
    TData m_data;
    size_t m_batchNum;
    // EvalBuffer<Batch<ElementType, DeviceType, CategoryTags::Matrix>>
    // m_evalBuf;
};

template <typename TData> class DuplicateImpl<TData, CategoryTags::Scalar> {
    static_assert(std::is_same_v<RemoveCVRef<TData>, TData>,
                  "Unavailable data type");

  public:
    using ElementType = typename TData::ElementType;
    using DeviceType = typename TData::DeviceType;

  public:
    DuplicateImpl(TData data, size_t batch_num)
        : m_data(std::move(data)), m_batchNum(batch_num) {
        assert(m_batchNum != 0);
    }

  public:
    [[nodiscard]] size_t Size() const noexcept { return m_batchNum; }

    [[nodiscard]] const TData& Element() const noexcept { return m_data; }

    [[nodiscard]] bool operator==(const Duplicate<TData>& val) const noexcept {
        decltype(auto) tmp =
            static_cast<const DuplicateImpl<TData, CategoryTags::Scalar>&>(val);
        return (tmp.m_data == m_data) && (tmp.m_batchNum == m_batchNum);
    }

    template <typename TOtherType>
    [[nodiscard]] bool operator==(const TOtherType&) const noexcept {
        return false;
    }

    template <typename TCompData>
    [[nodiscard]] bool operator!=(const TCompData& val) const noexcept {
        return !(operator==(val));
    }

  protected:
    TData m_data;
    size_t m_batchNum;
    // EvalBuffer<Batch<ElementType, DeviceType, CategoryTags::Matrix>>
    // m_evalBuf;
};

template <typename TData> auto MakeDuplicate(size_t batchNum, TData&& data) {
    using RawDataType = RemoveCVRef<TData>;
    return Duplicate<RawDataType>(std::forward<TData>(data), batchNum);
}

template <typename TData, typename... TParams>
auto MakeDuplicate(size_t batchNum, TParams&&... data) {
    using RawDataType = RemoveCVRef<TData>;
    RawDataType tmp(std::forward<TParams>(data)...);
    return Duplicate<RawDataType>(std::move(tmp), batchNum);
}

} // namespace MetaNN

#endif // METANN_DATA_BATCH_DUPLICATE_H
