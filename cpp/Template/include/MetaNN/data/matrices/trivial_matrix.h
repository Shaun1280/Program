#ifndef METANN_DATA_MATRICES_TRIVIAL_MATRIX_H
#define METANN_DATA_MATRICES_TRIVIAL_MATRIX_H

#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/data/scalar.h>

namespace MetaNN {
namespace NStrivialMatrix {} // namespace NStrivialMatrix

template <typename TElem, typename TDevice, typename TScalar>
class TrivialMatrix {
  public:
    using ElementType = TElem;
    using DeviceType = TDevice;

  public:
    TrivialMatrix(size_t p_rowNum, size_t p_colNum, TScalar p_val)
        : m_rowNum(p_rowNum), m_colNum(p_colNum), m_val(p_val) {}

    [[nodiscard]] size_t RowNum() const noexcept { return m_rowNum; }

    [[nodiscard]] size_t ColNum() const noexcept { return m_colNum; }

    [[nodiscard]] auto EvalValue() const noexcept { return m_val; }

  private:
    size_t m_rowNum;
    size_t m_colNum;
    TScalar m_val;
    // EvalBuffer<Matrix<ElementType, DeviceType>> m_buffer;
};

template <typename TElem, typename TDevice, typename TScalar>
static constexpr bool IsMatrix<TrivialMatrix<TElem, TDevice, TScalar>> = true;

template <typename TElem, typename TDevice, typename TVal>
auto MakeTrivialMatrix(size_t rowNum, size_t colNum, TVal&& m_val) {
    using RawVal = RemoveCVRef<TVal>;

    if constexpr (IsScalar<RawVal>) {
        // allow TrivialMatrix<float, GPU, Scalar<int, CPU>>
        static_assert(
            std::is_same_v<typename RawVal::DeviceType, TDevice> ||
            std::is_same_v<typename RawVal::DeviceType, DeviceTags::CPU>);
        return TrivialMatrix<TElem, TDevice, RawVal>(rowNum, colNum,
                                                     std::forward<TVal>(m_val));
    } else {
        TElem tmpElem = static_cast<TElem>(m_val);
        Scalar<TElem, DeviceTags::CPU> tmpScalar(std::move(tmpElem));
        return TrivialMatrix<TElem, TDevice, decltype(tmpScalar)>(
            rowNum, colNum, std::move(tmpScalar));
    }
}

} // namespace MetaNN

#endif // METANN_DATA_MATRICES_TRIVIAL_MATRIX_H