#ifndef METANN_DATA_BATCH_ARRAY_H
#define METANN_DATA_BATCH_ARRAY_H

/**
 * @file array.h
 * This file provides the implementation of Array, which is a dynamic batch of
 * data.
 */

#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/facilities/traits.h>
#include <cassert>
#include <memory>
#include <vector>

namespace MetaNN {

template <typename TData, typename TDataCate> class ArrayImpl;

// Array accepts Matrix, Scalar, ...
// Should have different behaviors for different data categories
template <typename TData> class Array : ArrayImpl<TData, DataCategory<TData>> {
  public:
    using ElementType = typename TData::ElementType;
    using DeviceType = typename TData::DeviceType;

    // inheritance constructor
    using ArrayImpl<TData, DataCategory<TData>>::ArrayImpl;
};

// If element type is matrix, then the array is batch matrix
template <typename TData>
constexpr bool IsBatchMatrix<Array<TData>> = IsMatrix<TData>;

// If element type is scalar, then the array is batch scalar
template <typename TData>
constexpr bool IsBatchScalar<Array<TData>> = IsScalar<TData>;

template <typename TData> class ArrayImpl<TData, CategoryTags::Matrix> {
  public:
    using ElementType = typename TData::ElementType;
    using DeviceType = typename TData::DeviceType;

  public:
    ArrayImpl(size_t rowNum = 0, size_t colNum = 0)
        : m_rowNum(rowNum), m_colNum(colNum),
          m_buffer(new std::vector<TData>()) {}

    template <typename TIterator,
              std::enable_if_t<IsIterator<TIterator>, bool> = true>
    ArrayImpl(TIterator begin, TIterator end)
        : m_rowNum(0), m_colNum(0),
          m_buffer(new std::vector<TData>(begin, end)) {
        const auto& buffer = *m_buffer;
        if (!buffer.empty()) {
            m_rowNum = buffer[0].RowNum();
            m_colNum = buffer[0].ColNum();

            for (size_t i = 1; i < buffer.size(); ++i) {
                if (buffer[i].RowNum() != m_rowNum ||
                    buffer[i].ColNum() != m_colNum) {
                    throw std::runtime_error("Dimension mismatch in ArrayImpl");
                }
            }
        }
    }

  public:
    [[nodiscard]] size_t RowNum() const noexcept { return m_rowNum; }
    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }

    [[nodiscard]] size_t BatchNum() const { return m_buffer->size(); }
    [[nodiscard]] size_t size() const { return m_buffer->size(); }

    void push_back(TData mat) {
        assert(AvailableForWrite());

        if ((mat.RowNum() != m_rowNum) || (mat.ColNum() != m_colNum)) {
            throw std::runtime_error("Dimension mismatch in ArrayImpl");
        }

        m_buffer->emplace_back(std::move(mat));
    }

    template <typename... TArgs> void emplace_back(TArgs&&... args) {
        assert(AvailableForWrite());

        TData mat(std::forward<TArgs>(args)...);
        if ((mat.RowNum() != m_rowNum) || (mat.ColNum() != m_colNum)) {
            throw std::runtime_error("Dimension mismatch in ArrayImpl");
        }

        m_buffer->emplace_back(std::move(mat));
    }

    void reserve(size_t num) {
        assert(AvailableForWrite());
        m_buffer->reserve(num);
    }

    void clear() {
        assert(AvailableForWrite());
        m_buffer->clear();
    }

    bool empty() const { return m_buffer->empty(); }

    const auto& operator[](size_t id) const { return (*m_buffer)[id]; }

    auto& operator[](size_t id) { return (*m_buffer)[id]; }

    [[nodiscard]] auto begin() { return m_buffer->begin(); }
    [[nodiscard]] auto begin() const { return m_buffer->begin(); }
    [[nodiscard]] auto end() { return m_buffer->end(); }
    [[nodiscard]] auto end() const { return m_buffer->end(); }

    [[nodiscard]] bool operator==(const Array<TData>& val) const noexcept {
        auto tmp =
            static_cast<const ArrayImpl<TData, CategoryTags::Matrix>&>(val);
        return m_buffer == tmp.m_buffer;
    }

    template <typename TOtherType>
    [[nodiscard]] bool operator==(const TOtherType&) const noexcept {
        return false;
    }

    template <typename TCompData>
    [[nodiscard]] bool operator!=(const TCompData& val) const noexcept {
        return !(operator==(val));
    }

    [[nodiscard]] bool AvailableForWrite() const {
        return m_buffer.use_count() == 1;
        // return (!m_evalBuf.IsEvaluated()) && (m_buffer.use_count() == 1);
    }

  protected:
    size_t m_rowNum;
    size_t m_colNum;
    std::shared_ptr<std::vector<TData>> m_buffer;
    // EvalBuffer<Batch<ElementType, DeviceType, CategoryTags::Matrix>>
    // m_evalBuf;
};

template <typename TData> class ArrayImpl<TData, CategoryTags::Scalar> {};

template <typename TIterator> auto MakeArray(TIterator begin, TIterator end) {
    using ElementType = typename std::iterator_traits<TIterator>::value_type;
    using RawData = RemoveCVRef<ElementType>;

    return Array<RawData>(begin, end);
}

} // namespace MetaNN

#endif // METANN_DATA_BATCH_ARRAY_H