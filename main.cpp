#include <iostream>
#include "babel.hpp"
#include "tester.hpp"
#include <cassert>





int main()
{


    std::cout << "Compiler is 64bit ? : " << babel::COMPILER_IS_64B << '\n';
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';
    auto T = babel::TIME::measure_time(1, TESTING::START_ALL_TEST, 1);
    std::cout << "Done\nTime : " << T << " seconds\n";

    std::cout << babel::LINUX::DISPLAY::get_screen_resolution().first << ", " << babel::LINUX::DISPLAY::get_screen_resolution().second << "\n";
    return 0;
}
