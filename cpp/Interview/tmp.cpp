#include <iostream>
#include <stdexcept>

// Implementation of a double-ended queue using a dynamic array of blocks
template <typename T> class deque {
  private:
    // Size of each block in the deque
    static constexpr size_t BLOCK_SIZE = 8;
    // Initial size of the map (array of block pointers)
    static constexpr size_t INITIAL_MAP_SIZE = 8;

    T** m_map;             // Array of pointers to blocks
    size_t m_map_size;     // Current size of the map
    size_t m_start_block;  // Index of first block containing elements
    size_t m_start_pos;    // Position in first block where elements start
    size_t m_finish_block; // Index of last block containing elements
    size_t m_finish_pos;   // Position in last block where elements end
    size_t m_size;         // Total number of elements in deque

    // Allocate a new block of memory
    T* allocate_block() { return new T[BLOCK_SIZE]; }

    // Deallocate a block of memory
    void deallocate_block(T* block) { delete[] block; }

    // Reallocate the map with a new size when more space is needed
    void reallocate_map(size_t new_map_size) {
        // Allocate new map
        T** new_map = new T*[new_map_size];
        // Calculate number of blocks needed
        size_t num_blocks = (m_size + BLOCK_SIZE - 1) / BLOCK_SIZE;
        // Calculate new starting position to center the blocks
        size_t new_start = (new_map_size - num_blocks) >> 1;

        // Copy existing blocks to new map
        for (size_t i = m_start_block; i <= m_finish_block; ++i) {
            new_map[new_start + (i - m_start_block)] = m_map[i];
        }

        delete[] m_map;

        // Update member variables
        m_map = new_map;
        m_finish_block = new_start + (m_finish_block - m_start_block);
        m_start_block = new_start;
        m_map_size = new_map_size;
    }

  public:
    // Constructor - initializes empty deque with one block
    deque()
        : m_map(nullptr), m_map_size(0), m_start_block(0), m_start_pos(0),
          m_finish_block(0), m_finish_pos(0), m_size(0) {
        m_map = new T*[INITIAL_MAP_SIZE];
        m_map_size = INITIAL_MAP_SIZE;
        m_start_block = m_finish_block = m_map_size >> 1;
        m_map[m_start_block] = allocate_block();
    }

    // Destructor - deallocates all blocks and map
    ~deque() {
        for (size_t i = m_start_block; i <= m_finish_block; ++i) {
            deallocate_block(m_map[i]);
        }
        delete[] m_map;
    }

    // Returns number of elements in deque
    size_t size() const { return m_size; }
    // Returns true if deque is empty
    bool empty() const { return m_size == 0; }

    // Add element to front of deque
    void push_front(const T& value) {
        if (m_start_pos == 0) {
            // Need new block for front
            if (m_start_block == 0) {
                // Need to reallocate map
                reallocate_map(m_map_size ? m_map_size * 2 : 1);
            }
            m_map[--m_start_block] = allocate_block();
            m_start_pos = BLOCK_SIZE;
        }
        m_map[m_start_block][--m_start_pos] = value;
        ++m_size;
    }

    // Add element to back of deque
    void push_back(const T& value) {
        if (m_finish_pos == BLOCK_SIZE) {
            // Need new block for back
            if (m_finish_block + 1 == m_map_size) {
                // Need to reallocate map
                reallocate_map(m_map_size ? m_map_size * 2 : 1);
            }
            m_map[++m_finish_block] = allocate_block();
            m_finish_pos = 0;
        }
        m_map[m_finish_block][m_finish_pos++] = value;
        ++m_size;
    }

    // Remove element from front of deque
    void pop_front() {
        if (empty()) {
            throw std::out_of_range("deque is empty");
        }
        ++m_start_pos;
        --m_size;
        if (m_start_pos == BLOCK_SIZE) {
            // Current block is empty, move to next
            deallocate_block(m_map[m_start_block]);
            ++m_start_block;
            m_start_pos = 0;
        }
    }

    // Remove element from back of deque
    void pop_back() {
        if (empty()) {
            throw std::out_of_range("deque is empty");
        }
        if (m_finish_pos == 0) {
            // Current block is empty, move to previous
            deallocate_block(m_map[m_finish_block]);
            --m_finish_block;
            m_finish_pos = BLOCK_SIZE;
        }
        --m_finish_pos;
        --m_size;
    }

    // Access element at given index
    T& operator[](size_t n) {
        size_t block = m_start_block + (m_start_pos + n) / BLOCK_SIZE;
        size_t pos = (m_start_pos + n) % BLOCK_SIZE;
        return m_map[block][pos];
    }

    // Access const element at given index
    const T& operator[](size_t n) const {
        size_t block = m_start_block + (m_start_pos + n) / BLOCK_SIZE;
        size_t pos = (m_start_pos + n) % BLOCK_SIZE;
        return m_map[block][pos];
    }

    // Output stream operator for printing deque contents
    friend std::ostream& operator<<(std::ostream& os, const deque<T>& q) {
        for (size_t i = 0; i < q.size(); ++i) {
            os << q[i] << " ";
        }
        return os;
    }
};

// Main function demonstrating deque usage
int main() {
    deque<int> q;
    // Push elements to back
    for (int i = 0; i < 10; ++i) {
        q.push_back(i);
    }
    std::cout << q << std::endl;

    // Remove elements from front
    for (int i = 0; i < 10; ++i) {
        q.pop_front();
    }

    // Push elements to front
    for (int i = 0; i < 10; ++i) {
        q.push_front(i);
    }
    std::cout << q << std::endl;

    // Remove elements from back
    for (int i = 0; i < 10; ++i) {
        q.pop_back();
    }
    std::cout << q << std::endl;

    // Push elements to back again
    for (int i = 0; i < 10; ++i) {
        q.push_back(i);
    }
    std::cout << q << std::endl;

    // Remove elements from back and print after each removal
    for (int i = 0; i < 10; ++i) {
        q.pop_back();
        std::cout << q << std::endl;
    }
    std::cout << q << std::endl;
    return 0;
}