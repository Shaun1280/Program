#pragma once

#include <shared_ptr.hpp>
#include <unique_ptr.hpp>

template <typename T, typename... Args>
    requires( !std::is_array_v<T> )
std::shared_ptr<T> make_shared( Args&&... args )
{
    return shared_ptr<T>( new T( std::forward<Args>( args )... ) );
}

template <typename T, typename... Args>
    requires( !std::is_array_v<T> )
std::unique_ptr<T> make_unique( Args&&... args )
{
    return unique_ptr<T>( new T( std::forward<Args>( args )... ) );
}
