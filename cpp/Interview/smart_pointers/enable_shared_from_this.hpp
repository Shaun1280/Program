#pragma once

#include "weak_ptr.hpp"
#include <type_traits>

template <typename T>
class enable_shared_from_this {
protected:
    constexpr enable_shared_from_this() noexcept = default;
    enable_shared_from_this(const enable_shared_from_this&) noexcept = default;
    enable_shared_from_this& operator=(const enable_shared_from_this&) noexcept = default;
    ~enable_shared_from_this() = default;

public:
    [[nodiscard]] shared_ptr<T> shared_from_this()
    {
        return shared_ptr<T>(m_weak_ptr);
    }

    [[nodiscard]] shared_ptr<const T> shared_from_this() const
    {
        return shared_ptr<const T>(m_weak_ptr);
    }

    [[nodiscard]] weak_ptr<T> weak_from_this() const noexcept
    {
        return m_weak_ptr;
    }

private:
    template <typename U>
    friend class shared_ptr;

    mutable weak_ptr<T> m_weak_ptr;
};

// Helper concept (optional) kept for readability
template <typename T>
concept shared_from_this_enabled = std::is_base_of_v<enable_shared_from_this<T>, T>;
