#ifndef METANN_DATA_SCALAR_H
#define METANN_DATA_SCALAR_H

#include <MetaNN/data/facilities/tags.h>
#include <MetaNN/data/facilities/traits.h>
#include <MetaNN/facilities/traits.h>

namespace MetaNN {

template <typename TElem, typename TDevice = DeviceTags::CPU> class Scalar {
    static_assert(std::is_same<RemoveCVRef<TElem>, TElem>::value);

  public:
    using ElementType = TElem;
    using DeviceType = TDevice;

  public:
    Scalar(ElementType elem = ElementType()) : m_elem(elem) {}

    [[nodiscard]] auto& Value() noexcept { return m_elem; }

    [[nodiscard]] auto Value() const noexcept { return m_elem; }

    bool operator==(const Scalar& val) const noexcept;

    template <typename TOtherType>
    bool operator==(const TOtherType& val) const noexcept;

    template <typename TData> bool operator!=(const TData& val) const noexcept;

    [[nodiscard]] auto EvalRegister() const noexcept;

  private:
    ElementType m_elem;
};

template <typename TElem, typename TDevice>
static constexpr bool IsScalar<Scalar<TElem, TDevice>> = true;

} // namespace MetaNN

#endif