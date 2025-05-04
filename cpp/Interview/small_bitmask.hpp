#include <bit>
#include <cassert>
#include <cstdint>
#include <functional>
#include <ostream>

template <size_t Size, typename UnderlyingTypeT = size_t>
class SmallBitMask {
   public:
    using underlying_type = UnderlyingTypeT;
    static_assert(std::is_unsigned_v<underlying_type> &&
                  !std::is_same_v<underlying_type, bool>);
    static constexpr size_t SizeCapacity = 8 * sizeof(underlying_type);
    static_assert(Size <= SizeCapacity);
    static constexpr underlying_type Max =
        (Size == SizeCapacity) ? ~(underlying_type{0})
                               : ((underlying_type{1} << Size) - 1u);

    constexpr SmallBitMask() = default;
    constexpr explicit SmallBitMask(underlying_type value)
        : _mask(Max & value) {}

    constexpr SmallBitMask operator&(const SmallBitMask& other) const {
        return SmallBitMask{_mask & other._mask};
    }

    constexpr SmallBitMask operator|(const SmallBitMask& other) const {
        return SmallBitMask{_mask | other._mask};
    }

    constexpr SmallBitMask& operator&=(const SmallBitMask& other) {
        _mask &= other._mask;
        return *this;
    }

    constexpr SmallBitMask& operator|=(const SmallBitMask& other) {
        _mask |= other._mask;
        return *this;
    }

    constexpr SmallBitMask& operator>>=(size_t pos) {
        _mask >>= pos;
        return *this;
    }

    constexpr SmallBitMask& operator<<=(size_t pos) {
        _mask = ((_mask << pos) & Max);
        return *this;
    }

    constexpr SmallBitMask operator>>(size_t pos) const {
        return SmallBitMask{_mask >> pos};
    }

    constexpr SmallBitMask operator<<(size_t pos) const {
        return SmallBitMask{(_mask << pos) & Max};
    }

    constexpr SmallBitMask operator~() const {
        return SmallBitMask{Max & (~_mask)};
    }

    constexpr bool operator==(SmallBitMask other) const {
        return _mask == other._mask;
    }

    constexpr bool any() const { return _mask != underlying_type{0u}; }
    constexpr bool all() const { return _mask == Max; }
    constexpr bool test(size_t index) const {
        return (index < Size) && bool(_mask & (underlying_type{1} << index));
    }

    explicit constexpr operator bool() const { return any(); }

    explicit constexpr operator int8_t() const = delete;
    explicit constexpr operator int16_t() const = delete;
    explicit constexpr operator int32_t() const = delete;
    explicit constexpr operator int64_t() const = delete;
    explicit constexpr operator uint8_t() const = delete;
    explicit constexpr operator uint16_t() const = delete;
    explicit constexpr operator uint32_t() const = delete;
    explicit constexpr operator uint64_t() const = delete;

    constexpr underlying_type getUnderlyingValue() const { return _mask; }

    underlying_type _mask = 0;
};