#include <cassert>
#include <utility>
#include <iostream>
#include "shared_ptr.hpp"

struct Foo : public enable_shared_from_this<Foo>
{
    int v;
    Foo(int x) : v(x) {}
};

int main()
{
    // Calling shared_from_this() on an object not managed by shared_ptr should throw.
    bool threw = false;
    try
    {
        Foo stack_foo(1);
        auto s = stack_foo.shared_from_this();
        (void)s;
    }
    catch (const std::bad_weak_ptr&)
    {
        threw = true;
    }
    assert(threw && "shared_from_this() must throw std::bad_weak_ptr when object is not owned by shared_ptr");

    // When owned by shared_ptr, shared_from_this() yields a shared_ptr to the same object and increments use_count.
    shared_ptr<Foo> p(new Foo(42));
    auto s1 = p->shared_from_this();
    assert(s1.get() == p.get());
    assert(p.use_count() == 2);

    s1.reset();
    assert(p.use_count() == 1);

    // Move ownership and verify still works
    shared_ptr<Foo> p2 = std::move(p);
    assert(p2.use_count() == 1);
    auto s2 = p2->shared_from_this();
    assert(s2.get() == p2.get());
    assert(s2.use_count() == 2);

    std::cout << "all passed" << std::endl;

    return 0;
}
