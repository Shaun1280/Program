#include <cstring>
#include <iostream>
#include <stdexcept>

class string {
  private:
    char* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_capacity) {
        char* new_data = new char[new_capacity];
        if (data_) {
            std::memcpy(new_data, data_, size_);
            delete[] data_;
        }
        data_ = new_data;
        capacity_ = new_capacity;
    }

  public:
    // Default constructor
    string() : data_(nullptr), size_(0), capacity_(0) {}

    // Constructor from C-string
    string(const char* str) {
        size_ = std::strlen(str);
        capacity_ = size_ + 1;
        data_ = new char[capacity_];
        std::memcpy(data_, str, size_);
    }

    // Copy constructor
    string(const string& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new char[capacity_];
        std::memcpy(data_, other.data_, size_);
    }

    // Move constructor
    string(string&& other) noexcept {
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Destructor
    ~string() { delete[] data_; }

    // Copy assignment operator
    string& operator=(const string& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = new char[capacity_];
            std::memcpy(data_, other.data_, size_);
        }
        return *this;
    }

    // Move assignment operator
    string& operator=(string&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Element access
    char& operator[](size_t pos) { return data_[pos]; }

    const char& operator[](size_t pos) const { return data_[pos]; }

    char& at(size_t pos) {
        if (pos >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[pos];
    }

    // Capacity
    size_t size() const { return size_; }
    size_t length() const { return size_; }
    bool empty() const { return size_ == 0; }
    size_t capacity() const { return capacity_; }

    // Modifiers
    void push_back(char c) {
        if (size_ + 1 > capacity_) {
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = c;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    // String operations
    string& operator+=(const string& str) {
        size_t new_size = size_ + str.size_;
        if (new_size > capacity_) {
            reallocate(new_size * 2);
        }
        std::memcpy(data_ + size_, str.data_, str.size_);
        size_ = new_size;
        return *this;
    }

    // Friend functions
    friend string operator+(const string& lhs, const string& rhs) {
        string result = lhs;
        result += rhs;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const string& str) {
        for (size_t i = 0; i < str.size_; ++i) {
            os << str.data_[i];
        }
        return os;
    }
};