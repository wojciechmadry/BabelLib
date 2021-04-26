#include <iostream>
#include "babel.hpp"
#include "tester.hpp"

#include <atomic>

int main()
{
    srand(time(nullptr));
    babel::TIME::timer t;
    t.start();
    TESTING::START_ALL_TEST(1);
    auto T = t.get_time();
    std::cout << "Done\nTime : " << T << " ms.\n";
    auto s = babel::FILE_SYS::load_txt("../loremipsum.txt");
    babel::TEXT::text tx(s);
    t.start();


    return 0;
}
