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

    std::ifstream f{"../.gitignore"};
    std::ifstream f1{"../.gitignore"};
    std::ifstream f2{"../.gitignore"};
    std::ifstream f3{"../.gitignore"};
    std::string line;
    while(std::getline(f2, line))
    {
        std::cout << line << " - Wykonano \n";
    }
    std::cout << "-----\n";
    babel::ITERATOR::reader rd(f);
    babel::ITERATOR::reader rd1(f1);
    babel::ITERATOR::reader rd2(f3);


    while(rd)
    {
        std::cout << rd << " - Wykonano \n";
    }
    std::cout << "-----\n";
    for(const auto& Line : rd1)
    {
        std::cout << Line << " - Wykonano\n";
    }

    std::cout << "-----\n";
    rd2.read();
    for(const auto& Line : rd2)
    {
        std::cout << Line << "\n";
    }
    std::cout << "-----\n";
    return 0;
}
