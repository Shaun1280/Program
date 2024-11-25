#include <stdexcept>

template <typename T> class Queue {
  private:
    T* buffer;
    int capacity;
    int size;
    int head;
    int tail;

  public:
    Queue(int cap) : capacity(cap), size(0), head(0), tail(0) {
        buffer = new T[capacity];
    }

    ~Queue() { delete[] buffer; }

    bool empty() const { return size == 0; }

    bool full() const { return size == capacity; }

    void push_back(const T& item) {
        if (full()) {
            throw std::runtime_error("Queue is full");
        }

        buffer[tail] = item;
        tail = (tail + 1) % capacity;
        size++;
    }

    T pop_front() {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }

        T item = buffer[head];
        head = (head + 1) % capacity;
        size--;
        return item;
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return buffer[head];
    }

    const T& back() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty");
        }
        return buffer[(tail - 1 + capacity) % capacity];
    }
};

template <typename T> class Deque {
  private:
    T* buffer;
    int capacity;
    int size;
    int head;
    int tail;

  public:
    Deque(int cap) : capacity(cap), size(0), head(0), tail(0) {
        buffer = new T[capacity];
    }

    ~Deque() { delete[] buffer; }

    bool empty() const { return size == 0; }

    bool full() const { return size == capacity; }

    void push_front(const T& item) {
        if (full()) {
            throw std::runtime_error("Deque is full");
        }

        head = (head - 1 + capacity) % capacity;
        buffer[head] = item;
        size++;
    }

    void push_back(const T& item) {
        if (full()) {
            throw std::runtime_error("Deque is full");
        }

        buffer[tail] = item;
        tail = (tail + 1) % capacity;
        size++;
    }

    T pop_front() {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }

        T item = buffer[head];
        head = (head + 1) % capacity;
        size--;
        return item;
    }

    T pop_back() {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }

        tail = (tail - 1 + capacity) % capacity;
        T item = buffer[tail];
        size--;
        return item;
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        return buffer[head];
    }

    const T& back() const {
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        return buffer[(tail - 1 + capacity) % capacity];
    }
};