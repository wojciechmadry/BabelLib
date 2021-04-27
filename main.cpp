#include <iostream>
#include "babel.hpp"
#include "tester.hpp"

#include <atomic>

int main()
{
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';
    srand(time(nullptr));
    babel::TIME::timer t;
    t.start();
    TESTING::START_ALL_TEST(1);
    auto T = t.get_time();
    std::cout << "Done\nTime : " << T << " ms.\n";
    std::vector<int> p = {-3,3,2,4,5,12};


    return 0;
}
