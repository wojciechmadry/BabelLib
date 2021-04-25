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
    //0.0015011
    auto p = tx.find("OSTATNIE ZDANIE COS TAM");
  // auto p = s.find("OSTATNIE ZDANIE COS TAM");
    T = t.get_time();

    if(p == nullptr)
        std::cout <<"NULL";
    for(int i = 0 ; i < 3 ;++i)
    {
        std::cout << *p;
        ++p;
    }
    std::cout << T << '\n';
    return 0;
}
