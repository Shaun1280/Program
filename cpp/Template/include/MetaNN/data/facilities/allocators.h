#ifndef METANN_DATA_FACILITIES_ALLOCATORS_H
#define METANN_DATA_FACILITIES_ALLOCATORS_H

#include <MetaNN/data/facilities/tags.h>
#include <deque>
#include <memory>
#include <mutex>
#include <unordered_map>

namespace MetaNN {

template <typename TDevice> struct Allocator {};

template <> struct Allocator<DeviceTags::CPU> {
    template <typename TElem>
    [[nodiscard]] static std::shared_ptr<TElem> Allocate(std::size_t p_elementSize) {
        return std::shared_ptr<TElem>(new TElem[p_elementSize],
                                      [](TElem* ptr) { delete[] ptr; });
    }
};

} // namespace MetaNN

#endif // METANN_DATA_FACILITIES_ALLOCATORS_H