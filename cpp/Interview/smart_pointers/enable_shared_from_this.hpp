#pragma once

#include "weak_ptr.hpp"
#include <type_traits>

/*
Life cycle of an enable_shared_from_this<T> object (summary):
- When an object of type T is created as a raw object (stack or raw new) and not yet owned by a shared_ptr,
  calling shared_from_this() will fail (constructing a shared_ptr from an empty weak_ptr throws std::bad_weak_ptr).
- When a shared_ptr<T> is created owning the object (the shared_ptr constructor calls the helper in shared_ptr),
  the internal weak_ptr inside enable_shared_from_this is set to refer to the same control block.
- After that, calling shared_from_this() returns a new shared_ptr<T> that shares ownership (increments use count).
- When all shared_ptr owners are destroyed, the managed object is deleted; weak_from_this() (or the stored weak_ptr)
  will then be expired.
Notes:
- The shared_ptr helper only initializes the weak_ptr if it is currently expired, matching typical std behavior.
- Copy/move of enable_shared_from_this does not automatically change ownership; the weak_ptr is not propagated by default.
*/

template <typename T>
class enable_shared_from_this
{
protected:
    enable_shared_from_this() noexcept = default;
    enable_shared_from_this(const enable_shared_from_this&) noexcept = default; // don't propagate ownership here
    enable_shared_from_this& operator=(const enable_shared_from_this&) noexcept = default;
    enable_shared_from_this(enable_shared_from_this&&) noexcept = default;
    enable_shared_from_this& operator=(enable_shared_from_this&&) noexcept = default;
    ~enable_shared_from_this() = default;

public:
    // Return a shared_ptr<T> that shares ownership of *this.
    // If there is no owning shared_ptr, this will throw std::bad_weak_ptr.
    shared_ptr<T> shared_from_this()
    {
        return shared_ptr<T>(m_weak_ptr);
    }

    // const overload
    shared_ptr<T> shared_from_this() const
    {
        return shared_ptr<T>(m_weak_ptr);
    }

    // Return a weak_ptr referring to *this (may be expired).
    weak_ptr<T> weak_from_this() const noexcept
    {
        return m_weak_ptr;
    }

private:
    template <typename U>
    friend class shared_ptr; // allow shared_ptr helper to assign m_weak_ptr

    mutable weak_ptr<T> m_weak_ptr{};
};

// Helper concept (optional) kept for readability
template <typename T>
concept shared_from_this_enabled = std::is_base_of_v<enable_shared_from_this<T>, T>;
