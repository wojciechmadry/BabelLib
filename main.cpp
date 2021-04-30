#include <iostream>
#include "babel.hpp"
#include "tester.hpp"

#include <atomic>

int main()
{
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';
    srand(static_cast<unsigned>(time(nullptr)));
    auto T = babel::TIME::measure_time(1000, TESTING::START_ALL_TEST, 1);
    std::cout << "Done\nTime : " << T << " seconds\n";
    //auto p = babel::MATH::distance<float>(-3, 2, 4, 7);
   // std::cout << p;
    std::cin.get();
    std::cin.get();
    return 0;
}
