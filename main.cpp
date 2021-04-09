#include <iostream>
#include "babel.hpp"
#include "tester.hpp"

int main()
{
    babel::TIME::timer t;
    t.start();
    TESTING::START_ALL_TEST(1000);
    auto T = t.get_time();
    std::cout << "Done\nTime : " << T << " ms.\n";
    return 0;
}
