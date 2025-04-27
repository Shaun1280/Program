#include <iostream>
#include <memory>

class Any {
   public:
    template <typename T>
    explicit Any(T value) : holder_(new Holder<T>(value)) {}

    ~Any() = default;

   private:
    struct HolderBase {
        virtual ~HolderBase() = default;
    };

    template <typename T>
    struct Holder : HolderBase {
        Holder(T value) : value_(value) {}
        T value_;
    };

    std::unique_ptr<HolderBase> holder_;

    template <typename T>
    friend T any_cast(const Any& any);
};

template <typename T>
T any_cast(const Any& any) {
    auto holder = dynamic_cast<Any::Holder<T>*>(any.holder_.get());
    if (!holder) {
        throw std::bad_cast{};
    }
    return holder->value_;
}

int main() {
    Any a1(42);                    // Store an integer
    Any a2(std::string("Hello"));  // Store a string

    try {
        auto i = any_cast<int>(a1);
        auto s = any_cast<std::string>(a2);

        std::cout << "a1 contains: " << i << std::endl;
        std::cout << "a2 contains: " << s << std::endl;
    } catch (const std::bad_cast& e) {
        std::cout << "Bad cast!" << std::endl;
    }

    return 0;
}