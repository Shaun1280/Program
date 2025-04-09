// 主函数模板
template <typename T>
void func(T value) {}

// 错误 - 函数模板不能偏特化
template <typename T>
void func<T*>(T* value) {}  // 编译错误

// 正确 - 可以使用函数重载来实现类似效果
template <typename T>
void func(T* value) {}  // 这是一个新的函数模板

// 正确 - 函数模板可以全特化
template <>
void func(int value) {}