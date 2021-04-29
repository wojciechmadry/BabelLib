#include <iostream>
#include "babel.hpp"
#include "tester.hpp"

#include <atomic>

int main()
{
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';
    srand(time(nullptr));
    auto T = babel::TIME::measure_time(100, TESTING::START_ALL_TEST, 1);
    std::cout << "Done\nTime : " << T << " seconds\n";
    return 0;
}
