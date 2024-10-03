#include <atomic>
#include <iostream>

template <typename T> class shared_ptr {
  public:
    explicit shared_ptr(T* ptr = nullptr)
        : m_ptr(ptr), m_ref_count(new std::atomic<int>(1)) {}

    shared_ptr(const shared_ptr& other)
        : m_ptr(other.m_ptr), m_ref_count(other.m_ref_count) {
        if (m_ref_count) {
            ++(*m_ref_count);
        }
    }

    shared_ptr(shared_ptr&& other) noexcept
        : m_ptr(other.m_ptr), m_ref_count(other.m_ref_count) {
        other.m_ptr = nullptr;
        other.m_ref_count = nullptr;
    }

    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            if (m_ref_count && --(*m_ref_count) == 0) {
                delete m_ptr;
                delete m_ref_count;
            }
            m_ptr = other.m_ptr;
            m_ref_count = other.m_ref_count;
            ++(*m_ref_count);
        }
    }

    ~shared_ptr() {
        if (m_ref_count && --(*m_ref_count) == 0) {
            delete m_ptr;
            delete m_ref_count;
        }
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const noexcept { return m_ptr; }
    T* get() const noexcept { return m_ptr; }
    int use_count() const { return m_ref_count ? m_ref_count->load() : 0; }

  private:
    T* m_ptr;
    std::atomic<int>* m_ref_count;
};

int main() {
    shared_ptr<int> ptr1(new int(42));
    shared_ptr<int> ptr2 = ptr1; // 拷贝构造

    std::cout << "ptr1: " << *ptr1 << std::endl;
    std::cout << "ptr2: " << *ptr2 << std::endl;

    {
        shared_ptr<int> ptr3 = std::move(ptr1); // 移动构造
        std::cout << "ptr3: " << *ptr3 << std::endl;
    }

    // ptr1 现在为空，因为它的资源已经被移动到 ptr3 中
    if (ptr1.use_count() == 0) {
        std::cout << "ptr1 is empty" << std::endl;
    }

    if (ptr2.use_count() == 0) {
        std::cout << "ptr2 is empty" << std::endl;
    }
    return 0;
}