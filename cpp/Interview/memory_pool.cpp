#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

class MemoryPool {
  private:
    struct BlockHeader {
        size_t size;       // Size of the block
        bool is_free;      // Whether the block is free
        BlockHeader* next; // Next block in the list
        BlockHeader* prev; // Previous block in the list
    };

    struct FreeBlock {
        size_t size;
        BlockHeader* block;
    };

    static const size_t MIN_BLOCK_SIZE = 16;
    static const size_t ALIGNMENT = 8;

    char* memory_;                       // Raw memory buffer
    size_t total_size_;                  // Total size of the memory pool
    BlockHeader* first_block_;           // First block in the list
    std::vector<FreeBlock> free_blocks_; // List of free blocks sorted by size

    // Align size to ALIGNMENT bytes
    size_t align_size(size_t size) {
        return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
    }

    // Get actual block size including header
    size_t get_block_size(size_t requested_size) {
        return align_size(requested_size + sizeof(BlockHeader));
    }

    // Split a block if possible
    void split_block(BlockHeader* block, size_t size) {
        size_t remaining_size = block->size - size;
        if (remaining_size >= MIN_BLOCK_SIZE + sizeof(BlockHeader)) {
            // Create new block from remaining space
            BlockHeader* new_block = reinterpret_cast<BlockHeader*>(
                reinterpret_cast<char*>(block) + size);
            new_block->size = remaining_size;
            new_block->is_free = true;
            new_block->next = block->next;
            new_block->prev = block;

            if (block->next) {
                block->next->prev = new_block;
            }
            block->next = new_block;
            block->size = size;

            // Add new free block to free_blocks_
            free_blocks_.push_back({remaining_size, new_block});
            std::sort(free_blocks_.begin(), free_blocks_.end(),
                      [](const FreeBlock& a, const FreeBlock& b) {
                          return a.size < b.size;
                      });
        }
    }

    // Merge adjacent free blocks
    void merge_blocks(BlockHeader* block) {
        // Merge with next block if it's free
        if (block->next && block->next->is_free) {
            block->size += block->next->size;
            block->next = block->next->next;
            if (block->next) {
                block->next->prev = block;
            }

            // Remove merged block from free_blocks_
            free_blocks_.erase(
                std::remove_if(free_blocks_.begin(), free_blocks_.end(),
                               [block](const FreeBlock& fb) {
                                   return fb.block == block->next;
                               }),
                free_blocks_.end());
        }

        // Merge with previous block if it's free
        if (block->prev && block->prev->is_free) {
            block->prev->size += block->size;
            block->prev->next = block->next;
            if (block->next) {
                block->next->prev = block->prev;
            }

            // Remove merged block from free_blocks_
            free_blocks_.erase(std::remove_if(free_blocks_.begin(),
                                              free_blocks_.end(),
                                              [block](const FreeBlock& fb) {
                                                  return fb.block == block;
                                              }),
                               free_blocks_.end());

            // Update the size of the merged block in free_blocks_
            for (auto& fb : free_blocks_) {
                if (fb.block == block->prev) {
                    fb.size = block->prev->size;
                    break;
                }
            }
        }
    }

  public:
    MemoryPool(size_t size) : total_size_(size) {
        size = align_size(size);
        memory_ = new char[size];

        // Initialize first block
        first_block_ = reinterpret_cast<BlockHeader*>(memory_);
        first_block_->size = size;
        first_block_->is_free = true;
        first_block_->next = nullptr;
        first_block_->prev = nullptr;

        // Add to free blocks
        free_blocks_.push_back({size, first_block_});
    }

    ~MemoryPool() { delete[] memory_; }

    void* allocate(size_t size) {
        size_t required_size = get_block_size(size);

        // Find the smallest free block that fits
        auto it = std::lower_bound(free_blocks_.begin(), free_blocks_.end(),
                                   FreeBlock{required_size, nullptr},
                                   [](const FreeBlock& a, const FreeBlock& b) {
                                       return a.size < b.size;
                                   });

        if (it == free_blocks_.end()) {
            return nullptr; // No suitable block found
        }

        BlockHeader* block = it->block;
        block->is_free = false;

        // Remove from free blocks
        free_blocks_.erase(it);

        // Split block if possible
        split_block(block, required_size);

        // Return pointer to usable memory (after header)
        return reinterpret_cast<char*>(block) + sizeof(BlockHeader);
    }

    void deallocate(void* ptr) {
        if (!ptr)
            return;

        // Get block header
        BlockHeader* block = reinterpret_cast<BlockHeader*>(
            reinterpret_cast<char*>(ptr) - sizeof(BlockHeader));

        block->is_free = true;

        // Add to free blocks
        free_blocks_.push_back({block->size, block});
        std::sort(free_blocks_.begin(), free_blocks_.end(),
                  [](const FreeBlock& a, const FreeBlock& b) {
                      return a.size < b.size;
                  });

        // Merge with adjacent free blocks
        merge_blocks(block);
    }

    // Debug function to print memory layout
    void print_layout() {
        BlockHeader* current = first_block_;
        while (current) {
            std::cout << "Block at " << current << ": "
                      << "size=" << current->size << ", "
                      << "is_free=" << current->is_free << std::endl;
            current = current->next;
        }
    }
};

// Struct for testing different sizes
struct SmallObject {
    int x;
    double y;
};

struct LargeObject {
    double data[100];
    std::string name;
};

int main() {
    // Create a memory pool with 1MB of memory
    MemoryPool pool(1024 * 1024);

    // Allocate different types of objects
    std::cout << "Allocating objects of different sizes:\n";

    // Small allocations
    SmallObject* small1 =
        static_cast<SmallObject*>(pool.allocate(sizeof(SmallObject)));
    SmallObject* small2 =
        static_cast<SmallObject*>(pool.allocate(sizeof(SmallObject)));

    if (small1 && small2) {
        small1->x = 42;
        small1->y = 3.14;
        small2->x = 100;
        small2->y = 2.718;

        std::cout << "Small object 1: x=" << small1->x << ", y=" << small1->y
                  << "\n";
        std::cout << "Small object 2: x=" << small2->x << ", y=" << small2->y
                  << "\n";
    }

    // Large allocation
    LargeObject* large =
        static_cast<LargeObject*>(pool.allocate(sizeof(LargeObject)));
    if (large) {
        large->data[0] = 1.0;
        large->data[99] = 99.0;
        large->name = "Test Object";
        std::cout << "Large object: name=" << large->name << "\n";
    }

    // Print memory layout
    std::cout << "\nMemory layout after allocations:\n";
    pool.print_layout();

    // Deallocate some objects
    std::cout << "\nDeallocating small1 and large:\n";
    pool.deallocate(small1);
    pool.deallocate(large);

    // Print memory layout after deallocation
    std::cout << "\nMemory layout after deallocations:\n";
    pool.print_layout();

    // Try to allocate a medium-sized object
    std::cout << "\nAllocating medium-sized object:\n";
    int* medium = static_cast<int*>(pool.allocate(50 * sizeof(int)));
    if (medium) {
        for (int i = 0; i < 50; i++) {
            medium[i] = i;
        }
        std::cout << "Medium array first element: " << medium[0] << "\n";
        std::cout << "Medium array last element: " << medium[49] << "\n";
    }

    // Print final memory layout
    std::cout << "\nFinal memory layout:\n";
    pool.print_layout();

    return 0;
}