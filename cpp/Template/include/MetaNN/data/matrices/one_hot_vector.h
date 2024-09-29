#ifndef METANN_DATA_MATRICES_ONE_HOT_VECTOR_H
#define METANN_DATA_MATRICES_ONE_HOT_VECTOR_H

#include <MetaNN/data/facilities/traits.h>

namespace MetaNN {

template <typename TElem, typename TDevice> class OneHotVector {
  public:
    using ElementType = TElem;
    using DeviceType = TDevice;

  public:
    OneHotVector(size_t p_colNum, size_t p_hotPos)
        : m_colNum(p_colNum), m_hotPos(p_hotPos) {}

    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }

    [[nodiscard]] size_t HotPos() const noexcept { return m_hotPos; }

  private:
    size_t m_colNum;
    size_t m_hotPos;
    // EvalBuffer<Matrix<ElementType, DeviceType>> m_buffer;
};

template <typename TElem, typename TDevice>
static constexpr bool IsMatrix<OneHotVector<TElem, TDevice>> = true;

} // namespace MetaNN

#endif // METANN_DATA_MATRICES_ONE_HOT_VECTOR_H