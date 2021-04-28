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
    std::vector<float> p = {0,3,12,5,-5,8,3};
   babel::ALGO::normalize(p);
   for(auto d : p)
       std::cout << d << ", ";
    return 0;
}
