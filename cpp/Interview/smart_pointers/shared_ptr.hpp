#pragma once

#include "weak_ptr.hpp"
#include <atomic>

template <typename T>
class shared_ptr
{
public:

private:
    template <typename U>
    friend class weak_ptr;

    T* m_ptr{ nullptr };
    shared_control_block* m_control_block{ nullptr };
};
