#include <iostream>
#include "babel.hpp"


int main()
{
    short p = -15;
    auto d = babel::ALGO::signed_unsigned_conv(p);
    std::cout <<size_t(d);
    return 0;
}
