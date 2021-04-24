#include <iostream>
#include "babel.hpp"
#include "tester.hpp"

#include <atomic>

int main()
{

    babel::TEXT::text tekst("Wojtek krolo zloty");
    srand(time(nullptr));
    babel::TIME::timer t;
    t.start();
    TESTING::START_ALL_TEST(1);
    auto T = t.get_time();
    std::cout << "Done\nTime : " << T << " ms.\n";

    std::atomic<int> d;
    babel::CONCEPTS::type_in_atomic<decltype(d)>::type TT;
    TT = 12;
    std::cout << std::is_same_v<decltype(d), int> << '\n';
    return 0;
}
