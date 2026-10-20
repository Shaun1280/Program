#include <tuple_elems_func_args_match.hpp>
#include <iostream>

void test_key_arg_type_match()
{
    tuple_elems_func_args_match obj;
    
    auto result = obj.is_inserted("topic", "key1", "key2", "key3", 42);
    if (result)
    {
        std::cout << "Inserted" << std::endl;
    }
    else
    {
        std::cout << "Not inserted" << std::endl;
    }

    auto result2 = obj.is_inserted("topic", "key1", "key2", "key3", 42);
    if (result2)
    {
        std::cout << "Inserted" << std::endl;
    }
    else
    {
        std::cout << "Not inserted" << std::endl;
    }
}

int main()
{
    test_key_arg_type_match();
    return 0;
}