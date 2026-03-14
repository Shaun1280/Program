#pragma once

#include <utility>

#include "control_block.hpp"
#include "shared_ptr.hpp"

template <typename T>
class weak_ptr
{
public:
    constexpr weak_ptr() noexcept = default;

    weak_ptr( const shared_ptr<T>& shared ) noexcept
        : m_ptr( shared.m_ptr )
        , m_control_block( shared.m_control_block )
    {
        if ( m_control_block )
        {
            m_control_block->increment_weak();
        }
    }

    weak_ptr( const weak_ptr& other ) noexcept
        : m_ptr( other.m_ptr )
        , m_control_block( other.m_control_block )
    {
        if ( m_control_block )
        {
            m_control_block->increment_weak();
        }
    }

    weak_ptr( weak_ptr&& other ) noexcept
        : m_ptr( std::exchange( other.m_ptr, nullptr ) )
        , m_control_block( std::exchange( other.m_control_block, nullptr ) )
    {
    }

    ~weak_ptr()
    {
        release();
    }

    weak_ptr& operator=( const weak_ptr& other ) noexcept
    {
        if ( this != &other )
        {
            release();
            m_ptr = other.m_ptr;
            m_control_block = other.m_control_block;
            if ( m_control_block )
            {
                m_control_block->increment_weak();
            }
        }
        return *this;
    }

    weak_ptr& operator=( weak_ptr&& other ) noexcept
    {
        if ( this != other )
        {
            release();
            m_ptr = std::exchange( other.m_ptr, nullptr );
            m_control_block = std::exchange( other.m_control_block, nullptr );
        }
        return *this;
    }

    weak_ptr& operator=( const shared_ptr<T>& shared ) noexcept
    {
        release();
        m_ptr = shared.m_ptr;
        m_control_block = shared.m_control_block;
        if ( m_control_block )
        {
            m_control_block->increment_weak();
        }
        return *this;
    }

    // Modifiers
    void reset() noexcept
    {
        release();
    }

    void swap( weak_ptr& other ) noexcept
    {
        std::swap( m_ptr, other.m_ptr );
        std::swap( m_control_block, other.m_control_block );
    }

    // Observers
    [[nodiscard]] int use_count() const noexcept
    {
        return m_control_block ? m_control_block->use_count() : 0;
    }

    [[nodiscard]] bool expired() const noexcept
    {
        return use_count() == 0;
    }

    [[nodiscard]] std::shared_ptr<T> lock() const noexcept
    {
        return expired() ? std::shared_ptr<T>() : std::shared_ptr<T>( *this );
    }

    [[nodiscard]] bool contains() const noexcept
    {
        return !expired();
    }

private:
    template <typename U>
    friend class shared_ptr;

    void release() noexcept
    {
        if ( m_control_block )
        {
            m_control_block->decrement_weak();
            m_control_block = nullptr;
            m_ptr = nullptr;
        }
    }

    T* m_ptr{ nullptr };
    shared_control_block* m_control_block{ nullptr };
};