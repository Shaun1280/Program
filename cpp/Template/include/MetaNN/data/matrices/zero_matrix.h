#ifndef METANN_DATA_MATRICES_ZERO_MATRIX_H
#define METANN_DATA_MATRICES_ZERO_MATRIX_H

#include <MetaNN/data/facilities/traits.h>

namespace MetaNN {

template <typename TElem, typename TDevice> class ZeroMatrix {
  public:
    using ElementType = TElem;
    using DeviceType = TDevice;

  public:
    ZeroMatrix(size_t p_rowNum, size_t p_colNum)
        : m_rowNum(p_rowNum), m_colNum(p_colNum) {}

    [[nodiscard]] size_t RowNum() const noexcept { return m_rowNum; }

    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }

  private:
    size_t m_rowNum;
    size_t m_colNum;
    // EvalBuffer<Matrix<ElementType, DeviceType>> m_buffer;
};

template <typename TElem, typename TDevice>
static constexpr bool IsMatrix<ZeroMatrix<TElem, TDevice>> = true;

} // namespace MetaNN

#endif // METANN_DATA_MATRICES_ZERO_MATRIX_H