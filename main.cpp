#include <iostream>
#include "babel.hpp"
#include "tester.hpp"

int main()
{

    babel::TEXT::text tekst("Wojtek krolo zloty");
    srand(time(nullptr));
    babel::TIME::timer t;
    t.start();
    TESTING::START_ALL_TEST(1);
    auto T = t.get_time();
    std::cout << "Done\nTime : " << T << " ms.\n";
    return 0;
}
