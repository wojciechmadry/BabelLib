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
    std::cout << babel::ALGO::CRYPT::sha512("hello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello world");
    //309ecc489c12d6eb4cc40f50c902f2b4d0ed77ee511a7c7a9bcd3ca86d4cd86f989dd35bc5ff499670da34255b45b0cfd830e81f605dcf7dc5542e93ae9cd76f
    return 0;
}
