#pragma once

#include "weak_ptr.hpp"
#include "enable_shared_from_this.hpp"

template <typename T>
class shared_ptr
{
public:
    constexpr shared_ptr() noexcept = default;

    template <typename U>
        requires std::is_convertible_v<U*, T*>
    explicit shared_ptr( U* ptr )
        : m_ptr( ptr )
        , m_control_block( ptr ? new shared_control_block( ptr, std::default_delete<U>() ) : nullptr )
    {
        enable_shared_from_this_helper(ptr);
    }

    /*
     * Two shared_ptr<T> objects with different deleters have the same type and can be assigned to each other.
     * shared_ptr can change its deleter at runtime through assignment from another shared_ptr
     */
    template <typename U, typename Deleter>
        requires std::is_convertible_v<U*, T*> && std::invocable<Deleter&, U*>
    shared_ptr( U* ptr, Deleter&& deleter )
        : m_ptr( ptr )
        , m_control_block( ptr ? new shared_control_block( ptr, std::forward<Deleter>( deleter ) ) : nullptr )
    {
        enable_shared_from_this_helper(ptr);
    }

    shared_ptr( shared_ptr& other ) noexcept
        : m_ptr( other.m_ptr )
        , m_control_block( other.m_control_block )
    {
        if ( m_control_block )
        {
            m_control_block->increment_shared();
        }
    }

    shared_ptr( shared_ptr&& other ) noexcept
        : m_ptr( other.m_ptr )
        , m_control_block( std::exchange( other.m_control_block, nullptr ) )
    {
    }

    // Constructor from weak_ptr
    explicit shared_ptr( const weak_ptr<T>& weak )
        : m_ptr( weak.m_ptr )
        , m_control_block( weak.m_control_block )
    {
        if ( !m_control_block || m_control_block->use_count() == 0 )
        {
            throw std::bad_weak_ptr();
        }
        m_control_block->increment_shared();
    }

    ~shared_ptr()
    {
        release();
    }

    shared_ptr& operator=( const shared_ptr& other ) noexcept
    {
        if ( this != &other )
        {
            release();
            m_ptr = other.m_ptr;
            m_control_block = other.m_control_block;
            if ( m_control_block )
            {
                m_control_block->increment_shared();
            }
        }
        return *this;
    }

    shared_ptr& operator=( shared_ptr&& other ) noexcept
    {
        if ( this != &other )
        {
            release();
            m_ptr = std::exchange( other.m_ptr, nullptr );
            m_control_block = std::exchange( other.m_control_block, nullptr );
        }
        return *this;
    }

    void reset() noexcept
    {
        release();
    }

    template <typename U>
        requires std::is_convertible_v<U*, T*>
    void reset( U* ptr )
    {
        release();
        m_ptr = ptr;
        if ( ptr )
        {
            m_control_block = new shared_control_block( ptr, std::default_delete<U>() );
            enable_shared_from_this_helper(ptr);
        }
    }

    template <typename U, typename Deleter>
        requires std::is_convertible_v<U*, T*>
    void reset( U* ptr, Deleter&& deleter )
    {
        release();
        m_ptr = ptr;
        if ( ptr )
        {
            m_control_block = new shared_control_block( ptr, std::forward<Deleter>( deleter ) );
            enable_shared_from_this_helper(ptr);
        }
    }

    void swap( shared_ptr& other ) noexcept
    {
        std::swap( m_ptr, other.m_ptr );
        std::swap( m_control_block, other.m_control_block );
    }

    [[nodiscard]] T* get() const noexcept
    {
        return m_ptr;
    }

    [[nodiscard]] T& operator*() const noexcept
    {
        return *m_ptr;
    }

    [[nodiscard]] T* operator->() const noexcept
    {
        return m_ptr;
    }

    [[nodiscard]] int use_count() const noexcept
    {
        return m_control_block ? m_control_block->use_count() : 0;
    }

    [[nodiscard]] explicit operator bool() const noexcept // no implicit conversion
    {
        return m_ptr != nullptr;
    }

    [[nodiscard]] bool unique() const noexcept
    {
        return use_count() == 1;
    }

    [[nodiscard]] bool contains() const noexcept
    {
        return m_ptr != nullptr;
    }

    [[nodiscard]] bool operator==( const shared_ptr& ) const noexcept = default;
    [[nodiscard]] bool operator!=( const shared_ptr& ) const noexcept = default;

    [[nodiscard]] bool operator==( std::nullptr_t ) const noexcept
    {
        return m_ptr == nullptr;
    }

    [[nodiscard]] bool operator!=( std::nullptr_t ) const noexcept
    {
        return m_ptr != nullptr;
    }

private:
    template <typename U>
    friend class weak_ptr;

    void release() noexcept
    {
        if ( m_control_block )
        {
            m_control_block->decrement_shared();
            m_control_block = nullptr;
            m_ptr = nullptr;
        }
    }

    T* m_ptr{ nullptr };
    shared_control_block* m_control_block{ nullptr };

    template <typename U>
    void enable_shared_from_this_helper(U* ptr) noexcept
    {
        if constexpr (std::is_base_of_v<enable_shared_from_this<U>, U>)
        {
            if (ptr && ptr->m_weak_ptr.expired())
            {
                ptr->m_weak_ptr = *this; // assign shared_ptr to weak_ptr
            }
        }
    }
};
