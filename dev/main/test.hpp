#include "config.hpp"
#include <iostream>

int main()
{
    std::cout << areNear( 0.0000000001, 0.000000000099 ) << '\n';
    std::cout << areNear( 1.0000000001, 1.000000000099 ) << '\n';
    std::cout << areNear( 1.00001, 1.0000099 ) << '\n';
    writeDebug("test");
    return 0;
}
