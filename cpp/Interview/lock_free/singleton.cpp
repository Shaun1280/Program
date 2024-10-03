#include <atomic>

class Singleton {
  public:
    static Singleton& getInstance() {
        if (auto tmp = m_instance.load(std::memory_order_acquire);
            tmp == nullptr) {
            // set flag to true, return its value before exchange (should be
            // false)
            if (!m_flag.exchange(true, std::memory_order_acq_rel)) {
                m_instance.store(new Singleton(), std::memory_order_release);
            } else { // m_flag is true, but instance may still be nullptr
                // Wait for the instance to be created
                while ((tmp = m_instance.load(std::memory_order_acquire)) ==
                       nullptr) {
                }
            }
        }
        return *m_instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

  private:
    Singleton() = default;
    ~Singleton() = default;

    static std::atomic<Singleton*> m_instance;
    static std::atomic<bool> m_flag;
};

// Initialize static members
std::atomic<Singleton*> Singleton::m_instance(nullptr);
std::atomic<bool> Singleton::m_flag(false);

int main() {
    Singleton& instance1 = Singleton::getInstance();
    return 0;
}