#include <iostream>
#include "babel.hpp"


int main()
{
    babel::GRAPHICS::rgb r(0, 0, 255);
    auto c = babel::GRAPHICS::RGB_TO_CMYK(r);
    std::cout << (int) c[0] << '\n';
    std::cout << (int) c[1] << '\n';
    std::cout << (int) c[2] << '\n';
    std::cout << (int) c[3] << '\n';
    return 0;
}
