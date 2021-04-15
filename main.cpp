#include <iostream>
#include "babel.hpp"
#include "tester.hpp"

int main()
{
    srand(time(nullptr));
    babel::TIME::timer t;
    t.start();
    TESTING::START_ALL_TEST(10000);
    auto T = t.get_time();
    std::cout << "Done\nTime : " << T << " ms.\n";
    return 0;
}
