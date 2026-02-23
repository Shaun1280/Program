#pragma once

#include "control_block.hpp"
#include "shared_ptr.hpp"
#include <utility>

template <typename T>
class weak_ptr
{
public:


private:
    template <typename U>
    friend class shared_ptr;

    void release() noexcept
    {
        if ( m_control_block )
        {
            m_control_block->decrement_weak();
        }
    }

    T* m_ptr{ nullptr };
    shared_control_block* m_control_block{ nullptr };
};