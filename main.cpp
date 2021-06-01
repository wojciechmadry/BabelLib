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

    std::list<std::string> lit = {"test", "tu", "test2"};
    std::vector<int> vit = {3,8,12,5,3,4,5};
    auto en = babel::ITERATOR::enumerate(vit.begin());
    auto f = *en;
    assert(f.get_index() == 0 && f.get_value() == 3);
    f.get_value() = 15;
    assert(f.get_value() == 15 && vit[0] == 15);
    ++en;
    assert((*en).get_index() == 1 && (*en).get_value() == 8);
    en++;
    assert((*en).get_index() == 2 && (*en).get_value() == 12);
    --en;
    assert((*en).get_index() == 1 && (*en).get_value() == 8);
    en--;
    assert((*en).get_index() == 0 && (*en).get_value() == 15);
    babel::ITERATOR::enumerate<decltype(vit.begin())>::value_type t = *en;
    assert(t.get_index() == 0 && t.get_value() == 15);
    int64_t good = 0;
    std::for_each(babel::ITERATOR::enumerate(vit.begin()), babel::ITERATOR::enumerate(vit.end()),[&good](const auto& data) mutable
    {
        assert(good == data.first());
        ++good;
    });
    good = 10;
    std::for_each(babel::ITERATOR::enumerate(lit.begin(), good), babel::ITERATOR::enumerate(lit.end(), good),[&good](const auto& data) mutable
    {
        assert(good == data.first());
        ++good;
    });

    good = 0;
    std::for_each(babel::ITERATOR::enumerate(lit.rbegin(), good), babel::ITERATOR::enumerate(lit.rend(), good),[&good](const auto& data) mutable
    {
        assert(good == data.first());
        ++good;
    });
    return 0;
}
