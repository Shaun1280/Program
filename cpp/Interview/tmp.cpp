#include <atomic>
#include <iostream>
#include <shared_mutex>
#include <unordered_map>
#include <vector>

template <typename Key, typename Value> class LockFreeHashMap {
  private:
    struct Node {
        Key key;
        Value value;
        std::atomic<Node*> next;
    };

    std::vector<std::atomic<Node*>> buckets;
    std::shared_mutex mutex;

    // Hash函数
    size_t hash(const Key& key) {
        return std::hash<Key>{}(key) % buckets.size();
    }

  public:
    LockFreeHashMap(size_t num_buckets) : buckets(num_buckets) {}

    void insert(const Key& key, const Value& value) {
        size_t idx = hash(key);
        Node* new_node = new Node{key, value, nullptr};

        Node* head = buckets[idx];
        new_node->next = head;

        while (!buckets[idx].compare_exchange_weak(head, new_node)) {
            new_node->next = head;
        }
    }

    bool find(const Key& key, Value& value) {
        size_t idx = hash(key);
        Node* current = buckets[idx];

        while (current) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }

        return false;
    }
};

int main() {
    LockFreeHashMap<int, std::string> map(10);

    map.insert(1, "One");
    map.insert(2, "Two");
    map.insert(3, "Three");

    std::string value;
    if (map.find(2, value)) {
        std::cout << "Value found: " << value << std::endl;
    } else {
        std::cout << "Value not found" << std::endl;
    }

    return 0;
}