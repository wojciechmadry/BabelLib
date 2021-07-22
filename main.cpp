#include <iostream>
#include "babel.hpp"
#include "tester.hpp"


int main()
{
    std::cout << "Compiler is 64bit ? : " << babel::COMPILER_IS_64B << '\n';
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';
    auto T = babel::TIME::measure_time(1, TESTING::START_ALL_TEST, 1);
    std::cout << "Done\nTime : " << T << " seconds\n";
    /*
    babel::TIME::timer t;
    std::vector<std::string> ves;
    for(std::size_t i = 1 ; i <= 1000 ; ++i)
    {
        std::string s;
        for(std::size_t j = 0 ; j < i ; ++j)
        {
            s.push_back('a');
        }
        ves.emplace_back(std::move(s));
    }

    std::size_t my_hash = 0;
    std::size_t i = 0;
    t.start();
    while(t.get_time_mili() <= 60000)
    {
        auto str = babel::ALGO::CRYPT::sha1(ves[i%ves.size()]);
        str.clear();
        ++i;
        ++my_hash;
    }
    std::cout << "C++ hash do : " << my_hash << " hash per minute\n";
     */
    return 0;
}
