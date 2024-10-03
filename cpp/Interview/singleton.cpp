// Lazy loaded singleton
class Singleton {
  public:
    // Delete copy constructor and assignment operator to prevent copies
    Singleton(const Singleton&) = delete;
    Singleton& /* shoulde be reference */ operator=(const Singleton&) = delete;

    // Static method to get the single instance of the class
    static Singleton& getInstance() {
        static Singleton instance; // Guaranteed to be thread-safe since C++11
        return instance;
    }

    // static Singleton instance;

  private:
    Singleton() = default;
    ~Singleton() = default;
};

// non-lazy Static member definition
// Singleton Singleton::instance;

int main() {
    // Access the Singleton instance
    Singleton& instance1 = Singleton::getInstance();
    return 0;
}