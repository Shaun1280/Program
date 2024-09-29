#ifndef METANN_DATA_FACILITIES_CONTINUOUS_MEMORY_H
#define METANN_DATA_FACILITIES_CONTINUOUS_MEMORY_H

#include <MetaNN/data/facilities/allocators.h>
#include <MetaNN/facilities/traits.h>

namespace MetaNN {

template <typename TElem, typename TDevice> class ContinuousMemory {
    static_assert(std::is_same_v<RemoveCVRef<TElem>, TElem>);
    using ElementType = TElem;
    using DeviceType = TDevice;

  public:
    explicit ContinuousMemory(std::size_t p_size)
        : m_mem(Allocator<TDevice>::template Allocate<TElem>(p_size)),
          m_memStart(m_mem.get()) {}

    ContinuousMemory(std::shared_ptr<ElementType> p_mem,
                     std::size_t p_size) noexcept
        : m_mem(std::move(p_mem)), m_memStart(m_mem.get()) {}

    [[nodiscard]] auto RawMemory() const noexcept { return m_memStart; }

    [[nodiscard]] const std::shared_ptr<ElementType>
    SharedPtr() const noexcept {
        return m_mem;
    }

    bool operator==(const ContinuousMemory& rhs) const noexcept {
        return m_mem == rhs.m_mem && m_memStart == rhs.m_memStart;
    }

    bool operator!=(const ContinuousMemory& rhs) const noexcept {
        return !(operator==(rhs));
    }

    [[nodiscard]] size_t UseCount() const noexcept { return m_mem.use_count(); }

  private:
    std::shared_ptr<ElementType> m_mem;
    ElementType* m_memStart;
};

} // namespace MetaNN

#endif