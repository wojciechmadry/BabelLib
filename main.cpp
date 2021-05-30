#include <iostream>
#include "babel.hpp"
#include "tester.hpp"

#include <atomic>


int main()
{

    std::cout << "Compiler is 64bit ? : " << babel::COMPILER_IS_64B <<'\n';
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';

    srand(static_cast<unsigned>(time(nullptr)));
    auto T = babel::TIME::measure_time(1, TESTING::START_ALL_TEST, 1);
    std::cout << "Done\nTime : " << T << " seconds\n";




    return 0;
}
