#include <iostream>
#include "babel.hpp"


int main()
{
    constexpr int k = 4;
    babel::CONCEPTS::type_of_number<k>::type itt;
   // decltype(itt)
    std::cout << (int)std::numeric_limits<decltype(itt)>::max() << '\n';
    std::cout << (int)std::numeric_limits<decltype(itt)>::min() << '\n';
    return 0;
}
