#include <iostream>
#include <memory>  // For std::allocator
#include <utility> // For std::move and std::forward

template <typename T, typename Allocator = std::allocator<T>>
class Vector : private Allocator {
  public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using AllocatorTraits = std::allocator_traits<Allocator>;
    using pointer = typename AllocatorTraits::pointer;
    using const_pointer = typename AllocatorTraits::const_pointer;

    // Iterators
    using iterator = T*;
    using const_iterator = const T*;

  public:
    // Default constructor
    Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

    // Destructor
    ~Vector() {
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
        AllocatorTraits::construct(get_allocator(), m_data + m_size, value);
        ++m_size;
    }

    void push_back(T&& value) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        AllocatorTraits::construct(get_allocator(), m_data + m_size,
                                   std::move(value));
        // equal to 使用 placement new 在 m_data + m_size 的位置上直接构造对象
        // new (place) T(args...)
        // new (m_data + m_size) T(std::forward<Args>(args)...);
        ++m_size;
    }

    // Emplace back
    template <typename... Args> void emplace_back(Args&&... args) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        AllocatorTraits::construct(get_allocator(), m_data + m_size,
                                   std::forward<Args>(args)...);
        ++m_size;
    }

    // Pop back
    void pop_back() {
        if (m_size > 0) {
            --m_size;
            AllocatorTraits::destroy(get_allocator(), m_data + m_size);
        }
    }

    // Clear
    void clear() {
        for (size_type i = 0; i < m_size; ++i) {
            AllocatorTraits::destroy(get_allocator(), m_data + i);
        }
        m_size = 0;
    }

  protected:
    size_type m_size;
    size_type m_capacity;
    pointer m_data;

    // Helper to access the allocator (since we inherit it)
    Allocator& get_allocator() noexcept { return *this; }
    const Allocator& get_allocator() const noexcept { return *this; }

    // Deallocate memory
    void deallocate() {
        if (m_data) {
            AllocatorTraits::deallocate(get_allocator(), m_data, m_capacity);
            // for (size_t i = 0; i < m_size; ++i) {
            //     m_data[i].~T();
            // }
            // ::operator delete(m_data);
            m_data = nullptr;
        }
    }

    void reallocate(size_type new_capacity) {
        pointer new_data =
            AllocatorTraits::allocate(get_allocator(), new_capacity);
        std::uninitialized_move(m_data, m_data + m_size, new_data);
        for (size_type i = 0; i < m_size; ++i) {
            AllocatorTraits::destroy(get_allocator(), m_data + i);
        }
        deallocate();
        m_data = new_data;
        m_capacity = new_capacity;

        // T* new_data = static_cast<T*>(::operator new(new_capacity *
        // sizeof(T))); for (size_t i = 0; i < m_size; ++i) {
        //     new (new_data + i) T(std::move(m_data[i]));
        //     m_data[i].~T();
        // }
        // ::operator delete(m_data);
    }
};

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
        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
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
            delete[] m_data;
            m_data = nullptr;
        }
    }

    void reallocate(size_type new_capacity) {
        pointer new_data = static_cast<pointer>(
            ::operator new(new_capacity * sizeof(value_type)));
        std::uninitialized_move(m_data, m_data + m_size, new_data);
        deallocate();
        m_data = new_data;
        m_capacity = new_capacity;
    }
};

// Example usage
int main() {
    Vector2<int> vec;

    // Print the size of the Vector class
    std::cout << "sizeof(Vector<int>): " << sizeof(vec) << " bytes"
              << std::endl;

    vec.push_back(1);
    vec.push_back(2);
    vec.emplace_back(3);
    vec.emplace_back(4);

    // Print vector contents
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    vec.pop_back();
    vec.pop_back();

    // Print vector contents after pop
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // for (auto x : vec) {
    //     std::cout << x << " ";
    // }

    // std::cout << std::endl;

    return 0;
}