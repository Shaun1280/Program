#include <iostream>
#include <iterator> // For std::iterator_traits
#include <memory>   // For std::allocator
#include <utility>  // For std::move and std::forward

template <typename T, typename Allocator = std::allocator<T>>
class Vector : private Allocator {
  public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer =
        typename std::allocator_traits<Allocator>::const_pointer;

    // Iterators
    using iterator = T*;
    using const_iterator = const T*;

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
        std::allocator_traits<Allocator>::construct(get_allocator(),
                                                    m_data + m_size, value);
        ++m_size;
    }

    void push_back(T&& value) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        std::allocator_traits<Allocator>::construct(
            get_allocator(), m_data + m_size, std::move(value));
        ++m_size;
    }

    // Emplace back
    template <typename... Args> void emplace_back(Args&&... args) {
        if (m_size >= m_capacity) {
            reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
        }
        std::allocator_traits<Allocator>::construct(
            get_allocator(), m_data + m_size, std::forward<Args>(args)...);
        ++m_size;
    }

    // Pop back
    void pop_back() {
        if (m_size > 0) {
            --m_size;
            std::allocator_traits<Allocator>::destroy(get_allocator(),
                                                      m_data + m_size);
        }
    }

    // Clear
    void clear() {
        for (size_type i = 0; i < m_size; ++i) {
            std::allocator_traits<Allocator>::destroy(get_allocator(),
                                                      m_data + i);
        }
        m_size = 0;
    }

  protected:
    pointer m_data;
    size_type m_size;
    size_type m_capacity;

    // Helper to access the allocator (since we inherit it)
    Allocator& get_allocator() noexcept { return *this; }
    const Allocator& get_allocator() const noexcept { return *this; }

    // Allocate memory
    void allocate(size_type n) {
        m_data = std::allocator_traits<Allocator>::allocate(get_allocator(), n);
    }

    // Deallocate memory
    void deallocate() {
        if (m_data) {
            std::allocator_traits<Allocator>::deallocate(get_allocator(),
                                                         m_data, m_capacity);
        }
    }

    // Reallocate memory
    void reallocate(size_type new_capacity) {
        pointer new_data = std::allocator_traits<Allocator>::allocate(
            get_allocator(), new_capacity);
        std::uninitialized_move(m_data, m_data + m_size, new_data);
        for (size_type i = 0; i < m_size; ++i) {
            std::allocator_traits<Allocator>::destroy(get_allocator(),
                                                      m_data + i);
        }
        deallocate();
        m_data = new_data;
        m_capacity = new_capacity;
    }
};

// Example usage
int main() {
    Vector<int> vec;

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

    return 0;
}