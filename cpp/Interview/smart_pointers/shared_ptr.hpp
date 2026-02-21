#pragma once

#include <atomic>

template <typename T>
class shared_ptr
{
public:
    explicit shared_ptr(T* ptr = nullptr) : m_ptr(ptr), m_ref_count(new std::atomic(1))
    {
    }

    shared_ptr(const shared_ptr& other) : m_ptr(other.m_ptr), m_ref_count(other.m_ref_count)
    {
        if (m_ref_count)
        {
            ++(*m_ref_count);
        }
    }

    shared_ptr(shared_ptr&& other) noexcept : m_ptr(other.m_ptr), m_ref_count(other.m_ref_count)
    {
        other.m_ptr       = nullptr;
        other.m_ref_count = nullptr;
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
        if (this != &other)
        {
            if (m_ref_count && --(*m_ref_count) == 0)
            {
                delete m_ptr;
                delete m_ref_count;
            }
            m_ptr       = other.m_ptr;
            m_ref_count = other.m_ref_count;
            ++(*m_ref_count);
        }
        return *this;
    }

    ~shared_ptr()
    {
        if (m_ref_count && --(*m_ref_count) == 0)
        {
            delete m_ptr;
            delete m_ref_count;
        }
    }

    T& operator*() const
    {
        return *m_ptr;
    }
    T* operator->() const noexcept
    {
        return m_ptr;
    }
    [[nodiscard]] T* get() const noexcept
    {
        return m_ptr;
    }
    [[nodiscard]] int use_count() const
    {
        return m_ref_count ? m_ref_count->load() : 0;
    }

private:
    T*                m_ptr;
    std::atomic<int>* m_ref_count;
};
