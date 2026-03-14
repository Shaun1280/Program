#include <iostream>
#include <shared_ptr.hpp>
#include <weak_ptr.hpp>
#include <unique_ptr.hpp>

int main()
{
    shared_ptr<int> sp1( new int( 42 ) );
    weak_ptr sp2( sp1 );

    unique_ptr up1( new int(100) );

    std::cout << sp2.expired() << std::endl;

    std::cout << *up1.get() << std::endl;
    return 0;
}