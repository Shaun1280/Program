#pragma once

#include <atomic>
#include <concepts>
#include <functional>
#include <memory>

template <typename T>
class shared_ptr;

template <typename T>
class weak_ptr;

template <typename D, typename T>
concept deleter_for = requires(D d, T* ptr) {
    { d(ptr) } -> std::same_as<void>;
};

class shared_control_block
{
    struct DeleterHolderBase
    {
        virtual ~DeleterHolderBase() = default;
        virtual void destroy(void*)  = 0;
    };

    template <typename T, typename Deleter>
    struct DeleterHolder final : DeleterHolderBase
    {
        explicit DeleterHolder(Deleter&& d) noexcept : m_deleter(std::forward<Deleter>(d))
        {
        }

        void destroy(void* ptr) override
        {
            m_deleter(static_cast<T*>(ptr));
        }

        Deleter m_deleter;
    };

public:
    template <typename T, deleter_for<T> Deleter>
    explicit shared_control_block(T* ptr, Deleter&& deleter) noexcept
        : m_ptr(ptr),
          m_ref_count(1),
          m_weak_count(0),
          m_deleter(new DeleterHolder<T, Deleter>(std::forward<Deleter>(deleter)))
    {
    }

    ~shared_control_block()
    {
        delete m_deleter;
    }

    // Strong reference counting
    void increment_shared() noexcept
    {
        m_ref_count.fetch_add(1, std::memory_order_relaxed);
    }

    bool decrement_shared() noexcept
    {
        if (m_ref_count.fetch_sub(1, std::memory_order_acq_rel) == 1)
        {
            // Last shared_ptr, delete the managed object using the deleter
            if (m_deleter)
            {
                m_deleter->destroy(m_ptr);
                m_ptr = nullptr;
            }

            if (m_weak_count.load(std::memory_order_acquire) == 0)
            {
                delete this; // self deletion is safe here, no ref/weak count
                return true;
            }
        }
        return false;
    }

    // Weak reference counting
    void increment_weak() noexcept
    {
        m_weak_count.fetch_add(1, std::memory_order_relaxed);
    }

    // Purpose of Weak References:
    // They don't keep the object alive (unlike shared_ptr)
    // They do keep the control block alive
    // They allow checking if the object still exists via expired() or lock()
    bool decrement_weak() noexcept
    {
        if (m_weak_count.fetch_sub(1, std::memory_order_acq_rel) == 1)
        {
            // Last weak_ptr, if no shared_ptrs, delete control block
            if (m_ref_count.load(std::memory_order_acquire) == 0)
            {
                delete this;
                return true;
            }
        }
        return false;
    }

    [[nodiscard]] int use_count() const noexcept
    {
        return m_ref_count.load(std::memory_order_acquire);
    }

    template <typename T>
    [[nodiscard]] T* get_ptr() const noexcept
    {
        return static_cast<T*>(m_ptr);
    }

private:
    void*              m_ptr;
    std::atomic<int>   m_ref_count;
    std::atomic<int>   m_weak_count;
    DeleterHolderBase* m_deleter;
};
