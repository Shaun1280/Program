#include <mutex>

class Singleton {
  public:
    static Singleton& getInstance() {
        if (m_instance == nullptr) { // First check (no locking)
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_instance == nullptr) { // Second check (with locking)
                m_instance = new Singleton();
            }
        }
        return *m_instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

  private:
    Singleton() = default;
    ~Singleton() = default;

    static Singleton* m_instance;
    static std::mutex m_mutex;
};

// Initialize static members
Singleton* Singleton::m_instance = nullptr;
std::mutex Singleton::m_mutex;

int main() {
    Singleton& instance1 = Singleton::getInstance();
    return 0;
}