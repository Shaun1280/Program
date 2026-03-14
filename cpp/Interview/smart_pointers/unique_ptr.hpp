#pragma once

#include <concepts>
#include <functional>
#include <type_traits>
#include <utility>

/*
 * Two unique_ptr<T, D1> and unique_ptr<T, D2> with different deleter types are incompatible types.
 * unique_ptr with default deleter has zero overhead (same size as raw pointer). With custom deleter, the size depends
 * on the deleter type.
 */
template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr
{
public:
    constexpr unique_ptr() noexcept = default;

    constexpr explicit unique_ptr( T* p ) noexcept
        : m_ptr( p )
    {
    }

    constexpr unique_ptr( T* p, Deleter&& d ) noexcept( std::is_nothrow_move_constructible_v<Deleter> ) // deleter is
                                                                                                        // not a
                                                                                                        // universal
                                                                                                        // reference,
                                                                                                        // it's not
                                                                                                        // template
                                                                                                        // <typename T>
                                                                                                        // func(T&&)
        requires std::is_move_constructible_v<Deleter>
        : m_ptr( p )
        , m_deleter( std::move( d ) )
    {
    }

    constexpr unique_ptr( T* p, const Deleter& d ) noexcept( std::is_nothrow_copy_constructible_v<Deleter> )
        requires std::is_copy_constructible_v<Deleter>
        : m_ptr( p )
        , m_deleter( d )
    {
    }

    template <typename U, typename D>
        requires std::is_convertible_v<U*, T*> && std::is_assignable_v<Deleter&, D&&> // assign from an rvalue to lvalue
    constexpr unique_ptr( unique_ptr<U, D>&& other ) noexcept // other is not a universal reference, it's not template
                                                              // <typename T> func(T&&)
        : m_ptr( other.release() )
        , m_deleter( std::move( other.get_deleter() ) )
    {
    }

    constexpr unique_ptr( unique_ptr&& other ) noexcept
        : m_ptr( other.release() )
        , m_deleter( std::move( other.m_deleter ) )
    {
    }

    constexpr unique_ptr& operator=( unique_ptr&& other ) noexcept
    {
        if ( this != other )
        {
            reset( other.release() );
            m_deleter = std::move( other.m_deleter );
        }
        return *this;
    }

    unique_ptr& operator=( const unique_ptr& ) = delete;
    unique_ptr( const unique_ptr& ) = delete;

    constexpr ~unique_ptr()
    {
        if ( m_ptr )
        {
            m_delete( m_ptr );
        }
    }

    // Modifiers
    [[nodiscard]] constexpr auto release() noexcept
    {
        auto p = m_ptr;
        m_ptr = nullptr;
        return p;
    }

    [[nodiscard]] constexpr Deleter& get_deleter() noexcept
    {
        return m_deleter;
    }

    constexpr void reset( T* p = nullptr ) noexcept
    {
        auto old = m_ptr;
        m_ptr = p;
        if ( old )
        {
            m_deleter( old );
        }
    }

    constexpr void swap( unique_ptr& other ) noexcept
    {
        std::swap( m_ptr, other.m_ptr );
        std::swap( m_deleter, other.m_deleter );
    }

    [[nodiscard]] constexpr const Deleter& get_deleter() const noexcept
    {
        return m_deleter;
    }

private:
    T* m_ptr{ nullptr };
    Deleter m_deleter{};
};