#include <iostream>
#include "babel.hpp"
#include "tester.hpp"
int main()
{
    /*std::cout << "Compiler is 64bit ? : " << babel::COMPILER_IS_64B << '\n';
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';
    srand(static_cast<unsigned>(time(nullptr)));
    auto T = babel::TIME::measure_time(1, TESTING::START_ALL_TEST, 1);
    std::cout << "Done\nTime : " << T << " seconds\n";
     */
    //std::cout << babel::ALGO::CRYPT::sha512("hello world");
    std::cout << babel::ALGO::CRYPT::sha1("hello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello world") << "\n";
    std::cout << babel::ALGO::CRYPT::sha224("hello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello world") << "\n";
    std::cout << babel::ALGO::CRYPT::sha256("hello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello world") << "\n";
    std::cout << babel::ALGO::CRYPT::sha512("hello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello world") << "\n";
    return 0;
}
