#include <iostream>
#include "babel.hpp"
#include "tester.hpp"

#include <atomic>


void show(int& p)
{
    while(p <= 100)
    std::cout << "Iter : " << ++p << "\n";
}

int show1(int& p)
{
    while(p <= 100)
        std::cout << "Iter : " << ++p << "\n";
    return p+ 1000;
}
int main()
{
    std::cout << "Compiler is 64bit ? : " << babel::COMPILER_IS_64B <<'\n';
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';

    srand(static_cast<unsigned>(time(nullptr)));
    auto T = babel::TIME::measure_time(1, TESTING::START_ALL_TEST, 1);
    std::cout << "Done\nTime : " << T << " seconds\n";
    auto disc = babel::WINDOWS::SYSTEM::all_discs();
    for(const auto& D : disc)
        std::cout << D << '\n';
    //std::cin.get();
    //std::cin.get();
    std::cout << "Is pointer :" << babel::CONCEPTS::IS_ANY_POINTER<int> << "\n";
    std::cout << "Is pointer :" << babel::CONCEPTS::IS_ANY_POINTER<int*> << "\n";
    std::cout << "Is pointer :" << babel::CONCEPTS::IS_ANY_POINTER<std::unique_ptr<int>> << "\n";
    std::cout << "Is pointer :" << babel::CONCEPTS::IS_ANY_POINTER<std::shared_ptr<int>> << "\n";
    std::cout << "Is pointer :" << babel::CONCEPTS::IS_ANY_POINTER<std::weak_ptr<int>> << "\n";
    std::cout << "Is pointer :" << babel::CONCEPTS::IS_ANY_POINTER<std::vector<int>> << "\n";
    std::cout << "Is pointer :" << babel::CONCEPTS::IS_ANY_POINTER<std::vector<int*>> << "\n";
    std::cout << "Is pointer :" << babel::CONCEPTS::IS_ANY_POINTER<std::string> << "\n";
    std::weak_ptr<int> w;
    std::unique_ptr<int> u;
    std::shared_ptr<int> s;

    return 0;
}
