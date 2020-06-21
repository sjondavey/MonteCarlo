#include <iostream>
#include "shared/bar.hpp"
#include "shared/foo.hpp"

int main()
{
    std::cout << "Hello, World!" << std::endl;

    Bar bar("foo");
    Foo foo(5);

    std::cout << bar.get() << std::endl;
    std::cout << foo.doubleValue() << std::endl;

    return 0;
}
