/*
 * this file just exists
 * don't bother to think about it
 */
#include "config.hpp"
void dummy_say_hello();

int main()
{
    plog::init(plog::debug,"log/dummy.log");
PLOGN << "Its a wonderful day";
    dummy_say_hello();
    return 0;
}
