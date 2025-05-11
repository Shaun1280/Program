#include <bit>
#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
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
        (Size == SizeCapacity)
            ? static_cast<underlying_type>(~underlying_type{0})
            : static_cast<underlying_type>((underlying_type{1} << Size) -
                                           underlying_type{1});

    constexpr SmallBitMask() = default;
    constexpr explicit SmallBitMask(underlying_type value)
        : _mask(static_cast<underlying_type>(Max & value)) {}
    constexpr explicit SmallBitMask(int value)
        : _mask(static_cast<underlying_type>(
              Max & static_cast<underlying_type>(value))) {}

    constexpr SmallBitMask operator&(const SmallBitMask& other) const {
        return SmallBitMask{static_cast<underlying_type>(_mask & other._mask)};
    }

    constexpr SmallBitMask operator|(const SmallBitMask& other) const {
        return SmallBitMask{static_cast<underlying_type>(_mask | other._mask)};
    }

    constexpr SmallBitMask& operator&=(const SmallBitMask& other) {
        _mask = static_cast<underlying_type>(_mask & other._mask);
        return *this;
    }

    constexpr SmallBitMask& operator|=(const SmallBitMask& other) {
        _mask = static_cast<underlying_type>(_mask | other._mask);
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
        return SmallBitMask{static_cast<underlying_type>(_mask >> pos)};
    }

    constexpr SmallBitMask operator<<(size_t pos) const {
        return SmallBitMask{static_cast<underlying_type>((_mask << pos) & Max)};
    }

    constexpr SmallBitMask operator~() const {
        return SmallBitMask{static_cast<underlying_type>(Max & (~_mask))};
    }

    constexpr bool operator==(const SmallBitMask& other) const {
        return _mask == other._mask;
    }

    constexpr bool operator!=(const SmallBitMask& other) const {
        return !(*this == other);
    }

    constexpr bool any() const { return _mask != underlying_type{0u}; }
    constexpr bool all() const { return _mask == Max; }
    constexpr bool none() const { return !any(); }
    constexpr bool test(size_t index) const {
        return (index < Size) && bool(_mask & (underlying_type{1} << index));
    }

    constexpr SmallBitMask& set(size_t index) {
        if (index < Size) {
            _mask |= (underlying_type{1} << index);
        }
        return *this;
    }

    constexpr SmallBitMask& reset(size_t index) {
        if (index < Size) {
            _mask &= ~(underlying_type{1} << index);
        }
        return *this;
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

namespace std {
template <size_t N, typename StoredT>
struct hash<SmallBitMask<N, StoredT>> {
    constexpr size_t operator()(
        const SmallBitMask<N, StoredT>& mask) const noexcept {
        return std::hash<size_t>{}(mask.getUnderlyingValue());
    }
};

template <size_t N, typename StoredT>
std::ostream& operator<<(std::ostream& os,
                         const SmallBitMask<N, StoredT>& mask) {
    os << "SmallBitMask<" << N << ", " << typeid(StoredT).name() << ">(";
    for (size_t i = N - 1; i >= 0; --i) {
        os << ((mask.test(i) ? '1' : '0'));
    }
    os << ")";
    return os;
}

}  // namespace std

// Tests
void runTests() {
    // Test construction and basic operations
    constexpr SmallBitMask<8, uint8_t> empty;
    assert(empty.none());
    assert(!empty.any());
    assert(!empty.all());
    assert(empty.getUnderlyingValue() == 0);

    constexpr SmallBitMask<8, uint8_t> full(0xFF);
    assert(!full.none());
    assert(full.any());
    assert(full.all());
    assert(full.getUnderlyingValue() == 0xFF);

    // Test bitwise operations
    constexpr SmallBitMask<8, uint8_t> a(0b10101010);
    constexpr SmallBitMask<8, uint8_t> b(0b11110000);

    auto c = a & b;
    assert(c.getUnderlyingValue() == 0b10100000);

    auto d = a | b;
    assert(d.getUnderlyingValue() == 0b11111010);

    auto e = ~a;
    assert(e.getUnderlyingValue() == 0b01010101);

    // Test shift operations
    auto f = a << 2;
    assert(f.getUnderlyingValue() == 0b10101000);

    auto g = a >> 2;
    assert(g.getUnderlyingValue() == 0b00101010);

    // Test individual bit operations
    SmallBitMask<8, uint8_t> h;
    h.set(3);
    assert(h.test(3));
    assert(!h.test(4));

    h.reset(3);
    assert(!h.test(3));

    // Test comparison operators
    assert(a == a);
    assert(a != b);

    // Test boundary conditions
    SmallBitMask<8, uint8_t> i(0x100);    // Value exceeds 8 bits
    assert(i.getUnderlyingValue() == 0);  // Should be masked to 0

    i |= SmallBitMask<8, uint8_t>(0xEF);
    assert(i.getUnderlyingValue() == 0xEF);  // Should be 0xFF
    std::cout << i << "\n";
}

int main() {
    runTests();
    std::cout << "All tests passed!\n";
    return 0;
}