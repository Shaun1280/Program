#ifndef METANN_DATA_MATRICES_CPU_MATRIX_H
#define METANN_DATA_MATRICES_CPU_MATRIX_H

#include <MetaNN/data/batch/batch.h>
#include <MetaNN/data/facilities/continuous_memory.h>
#include <MetaNN/data/facilities/lower_access.h>
#include <MetaNN/data/facilities/tags.h>
#include <MetaNN/data/facilities/traits.h>
#include <cassert>

namespace MetaNN {

// forward declaration
template <typename TElem>
struct LowerAccessImpl<Matrix<TElem, DeviceTags::CPU>>;

// forward declaration
template <typename TElem, typename TDevice>
class Batch<TElem, TDevice, CategoryTags::Matrix>;

// matrix class implementation
template <typename TElem> class Matrix<TElem, DeviceTags::CPU> {
  public:
    using ElementType = TElem;
    using DeviceType = DeviceTags::CPU;

    friend struct LowerAccessImpl<Matrix<ElementType, DeviceType>>;
    friend class Batch<ElementType, DeviceType, CategoryTags::Matrix>;

  public:
    Matrix(size_t p_rowNum = 0, size_t p_colNum = 0)
        : m_mem(p_rowNum * p_colNum), m_rowNum(p_rowNum), m_colNum(p_colNum),
          m_rowLen(p_colNum) {}

    // dimension related
    [[nodiscard]] size_t RowNum() const noexcept { return m_rowNum; }
    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }

    // read-write access
    void SetValue(size_t p_rowId, size_t p_colId, ElementType val) {
        assert(AvailableForWrite());
        assert((p_rowId < m_rowNum) && (p_colId < m_colNum));
        auto memStart = m_mem.RawMemory();
        memStart[p_rowId * m_rowLen + p_colId] = val;
    }

    const auto operator()(size_t p_rowId, size_t p_colId) const noexcept {
        assert((p_rowId < m_rowNum) && (p_colId < m_colNum));
        return (m_mem.RawMemory())[p_rowId * m_rowLen + p_colId];
    }

    bool AvailableForWrite() const noexcept { return m_mem.UseCount() == 1; }

    // sub-matrix
    auto SubMatrix(size_t p_rowB, size_t p_rowE, size_t p_colB,
                   size_t p_colE) const {
        assert((p_rowB < m_rowNum) && (p_rowE <= m_rowNum));
        assert((p_colB < m_colNum) && (p_colE <= m_colNum));
        auto pos = m_mem.RawMemory() + p_rowB * m_rowLen + p_colB;
        return Matrix(m_mem.SharedPtr(), pos, p_rowE - p_rowB, p_colE - p_colB,
                      m_rowLen);
    }

  private:
    // private constructor
    Matrix(std::shared_ptr<ElementType> p_mem, ElementType* p_memStart,
           size_t p_rowNum, size_t p_colNum, size_t p_rowLen)
        : m_mem(p_mem, p_memStart), m_rowNum(p_rowNum), m_colNum(p_colNum),
          m_rowLen(p_rowLen) {}

  private:
    ContinuousMemory<ElementType, DeviceType> m_mem;
    size_t m_rowNum;
    size_t m_colNum;
    size_t m_rowLen;
};

// lower access implementation
template <typename TElem>
struct LowerAccessImpl<Matrix<TElem, DeviceTags::CPU>> {
    LowerAccessImpl(Matrix<TElem, DeviceTags::CPU> p_matrix)
        : m_matrix(p_matrix) {}

    [[nodiscard]] auto MutableRawMemory() const noexcept {
        return m_matrix.m_mem.RawMemory();
    }

    [[nodiscard]] const auto RawMemory() const noexcept {
        return m_matrix.m_mem.RawMemory();
    }

    [[nodiscard]] size_t RowLen() const noexcept { return m_matrix.m_rowLen; }

  private:
    Matrix<TElem, DeviceTags::CPU> m_matrix;
};

} // namespace MetaNN

#endif