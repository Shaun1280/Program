#include <iostream>
#include <memory>
#include <vector>

template <typename T> class ObjectPool {
  private:
    std::vector<std::shared_ptr<T>> pool; // 使用 shared_ptr 管理对象

  public:
    ObjectPool(int size) {
        for (int i = 0; i < size; ++i) {
            pool.push_back(std::make_shared<T>());
        }
    }

    std::shared_ptr<T> getObject() {
        if (pool.empty()) {
            pool.push_back(std::make_shared<T>());
            std::cout << "Created a new object in the pool." << std::endl;
        }

        std::shared_ptr<T> obj = pool.back();
        pool.pop_back();
        return obj;
    }

    void releaseObject(std::shared_ptr<T> obj) { pool.push_back(obj); }
};

// 示例用法
class MyObject {
  public:
    void doSomething() {
        std::cout << "MyObject is doing something." << std::endl;
    }
};

int main() {
    ObjectPool<MyObject> objectPool(3);

    // 从对象池中获取对象并使用
    std::shared_ptr<MyObject> obj1 = objectPool.getObject();
    obj1->doSomething();

    // 将对象放回对象池
    objectPool.releaseObject(obj1);

    // 再次获取对象
    std::shared_ptr<MyObject> obj2 = objectPool.getObject();
    obj2->doSomething();

    return 0;
}