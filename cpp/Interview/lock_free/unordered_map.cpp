#include <atomic>
#include <iostream>
#include <vector>

template <typename Key, typename Value> class unordered_map {
  public:
    explicit unordered_map(size_t num_buckets) : buckets(num_buckets) {}

    void insert(const Key& key, const Value& value) {
        size_t idx = hash(key);
        Node* new_node = new Node{key, value, nullptr};

        Node* head = buckets[idx];
        new_node->next = head;

        // head is expected value, new_node is desired value
        while (!buckets[idx].compare_exchange_weak(head, new_node)) {
            // if fail to swap, head will be updated to the current value
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

    ~unordered_map() {
        for (size_t i = 0; i < buckets.size(); ++i) {
            Node* current = buckets[i];
            while (current) {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    }

  private:
    struct Node {
        Key key;
        Value value;
        std::atomic<Node*> next;
    };

    std::vector<std::atomic<Node*>> buckets;

    size_t hash(const Key& key) {
        return std::hash<Key>{}(key) % buckets.size();
    }
};

int main() {
    unordered_map<int, std::string> map(10);

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