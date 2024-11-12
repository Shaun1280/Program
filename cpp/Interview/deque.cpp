#include <iostream>
#include <stdexcept>

template <typename T> class deque {
  private:
    static const size_t BLOCK_SIZE = 512;     // 每个块的大小
    static const size_t INITIAL_MAP_SIZE = 8; // 初始映射表大小

    T** map_;             // 指向块指针数组的指针
    size_t map_size_;     // 映射表大小
    size_t start_block_;  // 第一个元素所在块
    size_t start_pos_;    // 第一个元素在块中的位置
    size_t finish_block_; // 最后一个元素所在块
    size_t finish_pos_;   // 最后一个元素在块中的位置
    size_t size_;         // 元素总数

    // 分配新块
    T* allocate_block() { return new T[BLOCK_SIZE]; }

    // 释放块
    void deallocate_block(T* block) { delete[] block; }

    // 重新分配映射表
    void reallocate_map(size_t new_map_size) {
        T** new_map = new T*[new_map_size];
        size_t blocks_needed = (size_ + BLOCK_SIZE - 1) / BLOCK_SIZE;
        size_t new_start = (new_map_size - blocks_needed) / 2;

        // 复制原有数据
        for (size_t i = start_block_; i <= finish_block_; ++i) {
            new_map[new_start + (i - start_block_)] = map_[i];
        }

        // 释放旧映射表
        delete[] map_;

        // 更新状态
        map_ = new_map;
        finish_block_ = new_start + (finish_block_ - start_block_);
        start_block_ = new_start;
        map_size_ = new_map_size;
    }

  public:
    deque()
        : map_(nullptr), map_size_(0), start_block_(0), start_pos_(0),
          finish_block_(0), finish_pos_(0), size_(0) {
        map_ = new T*[INITIAL_MAP_SIZE];
        map_size_ = INITIAL_MAP_SIZE;
        start_block_ = finish_block_ = map_size_ / 2;
        map_[start_block_] = allocate_block();
    }

    ~deque() {
        for (size_t i = start_block_; i <= finish_block_; ++i) {
            deallocate_block(map_[i]);
        }
        delete[] map_;
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    // 在前端插入元素
    void push_front(const T& value) {
        if (start_pos_ == 0) {
            if (start_block_ == 0) {
                reallocate_map(map_size_ * 2);
            }
            map_[start_block_ - 1] = allocate_block();
            start_block_--;
            start_pos_ = BLOCK_SIZE;
        }
        start_pos_--;
        map_[start_block_][start_pos_] = value;
        size_++;
    }

    // 在后端插入元素
    void push_back(const T& value) {
        if (finish_pos_ == BLOCK_SIZE) {
            if (finish_block_ + 1 == map_size_) {
                reallocate_map(map_size_ * 2);
            }
            map_[finish_block_ + 1] = allocate_block();
            finish_block_++;
            finish_pos_ = 0;
        }
        map_[finish_block_][finish_pos_] = value;
        finish_pos_++;
        size_++;
    }

    // 从前端删除元素
    void pop_front() {
        if (empty()) {
            throw std::out_of_range("deque is empty");
        }
        start_pos_++;
        size_--;
        if (start_pos_ == BLOCK_SIZE) {
            deallocate_block(map_[start_block_]);
            start_block_++;
            start_pos_ = 0;
        }
    }

    // 从后端删除元素
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("deque is empty");
        }
        if (finish_pos_ == 0) {
            deallocate_block(map_[finish_block_]);
            finish_block_--;
            finish_pos_ = BLOCK_SIZE;
        }
        finish_pos_--;
        size_--;
    }

    // 访问元素
    T& operator[](size_t n) {
        size_t block = start_block_ + (start_pos_ + n) / BLOCK_SIZE;
        size_t pos = (start_pos_ + n) % BLOCK_SIZE;
        return map_[block][pos];
    }

    const T& operator[](size_t n) const {
        size_t block = start_block_ + (start_pos_ + n) / BLOCK_SIZE;
        size_t pos = (start_pos_ + n) % BLOCK_SIZE;
        return map_[block][pos];
    }

    T& at(size_t n) {
        if (n >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return (*this)[n];
    }

    const T& at(size_t n) const {
        if (n >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return (*this)[n];
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("deque is empty");
        }
        return map_[start_block_][start_pos_];
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("deque is empty");
        }
        return finish_pos_ == 0 ? map_[finish_block_ - 1][BLOCK_SIZE - 1]
                                : map_[finish_block_][finish_pos_ - 1];
    }
};