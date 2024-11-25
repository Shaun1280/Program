#include <iostream>
#include <memory>  // For std::allocator
#include <utility> // For std::move and std::forward

template <typename T> class Vector2 {
  public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

    struct Iterator {
        pointer ptr;
        Iterator(pointer ptr) : ptr(ptr) {}
        Iterator& operator++() {
            ++ptr;
            return *this;
        }
        Iterator operator++(int) {
            Iterator temp = *this;
            ++ptr;
            return temp;
        }
        reference operator*() { return *ptr; }
    };

    using iterator = Iterator;
    using const_iterator = const Iterator;

  public:
    // Default constructor
    Vector2() : m_data(nullptr), m_size(0), m_capacity(0) {}

    // Destructor
    ~Vector2() {
        clear();
        deallocate();
    }

    // Size and capacity
    size_type size() const noexcept { return m_size; }
    size_type capacity() const noexcept { return m_capacity; }
    bool empty() const noexcept { return m_size == 0; }

    // Access elements
    reference operator[](size_type index) { return m_data[index]; }
    const_reference operator[](size_type index) const { return m_data[index]; }

    // Front and back
    reference front() { return m_data[0]; }
    const_reference front() const { return m_data[0]; }

    reference back() { return m_data[m_size - 1]; }
    const_reference back() const { return m_data[m_size - 1]; }

    // Iterators
    iterator begin() noexcept { return m_data; }
    const_iterator begin() const noexcept { return m_data; }
    iterator end() noexcept { return m_data + m_size; }
    const_iterator end() const noexcept { return m_data + m_size; }

    // Push back
    void push_back(const T& value) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        new (m_data + m_size) T(value);
        ++m_size;
    }

    void push_back(T&& value) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        new (m_data + m_size) T(std::move(value));
        ++m_size;
    }

    // Emplace back
    template <typename... Args> void emplace_back(Args&&... args) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        new (m_data + m_size) T(std::forward<Args>(args)...);
        ++m_size;
    }

    // Pop back
    void pop_back() {
        if (m_size == 0) {
            throw std::out_of_range("Vector2<>::pop_back(): empty vector");
        }
        m_data[--m_size].~T();
    }

    // Clear
    void clear() {
        for (size_type i = 0; i < m_size; ++i) {
            m_data[i].~T();
        }
        m_size = 0;
    }

  protected:
    size_type m_size;
    size_type m_capacity;
    pointer m_data;

    void deallocate() {
        if (m_data) {
            delte[] m_data;
            m_data = nullptr;
        }
    }

    void reallocate(size_type new_capacity) {
        pointer new_data = static_cast<pointer>(
            ::operator new(new_capacity * sizeof(value_type)));
        std::unitialized_move(m_data, m_data + m_size, new_data);
        deallocate();
        m_data = new_data;
        m_capacity = new_capacity;
    }
};