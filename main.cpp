#include <iostream>
#include "babel.hpp"
#include "tester.hpp"
#include <cassert>





int main()
{


    std::cout << "Compiler is 64bit ? : " << babel::COMPILER_IS_64B << '\n';
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';
    auto T = babel::TIME::measure_time(1, TESTING::START_ALL_TEST, 1);
    std::cout << "Done\nTime : " << T << " seconds\n";

    std::cout << babel::LINUX::DISPLAY::get_screen_resolution().first << ", " << babel::LINUX::DISPLAY::get_screen_resolution().second << "\n";

    using namespace babel::CHAR;

    constexpr const char* d1 = "TestConstexpr";  // 13
    constexpr const char* d2 = "VeryLongTextVeryLongTextVeryLongText";  // 36
    constexpr const char* d3 = "1234";  // 4

    constexpr const_char def; // no
    constexpr const_char cc1(d1);  // d1
    constexpr const_char cc2(d2);  // d2
    constexpr const_char cc3(d3); // d3
    constexpr const_char cc4(cc3); // d3
    static_assert(def.size() == 0 && def.data() == nullptr);
    static_assert(cc1.size() == 13 && cc1.data() != nullptr);
    static_assert(cc2.size() == 36 && cc2.data() != nullptr);
    static_assert(cc3.size() == 4 && cc3.data() != nullptr);
    static_assert(cc4.size() == 4 && cc4.data() != nullptr && cc4.data() == cc3.data());

    constexpr auto defCount = def.count('a');
    static_assert(defCount == 0);

    constexpr auto cc1Count = cc1.count('a');
    constexpr auto cc1Count2 = cc1.count('e');
    static_assert(cc1Count == 0 && cc1Count2 == 2);

    constexpr auto cc2Count = cc2.count('a');
    constexpr auto cc2Count2 = cc2.count('V');
    static_assert(cc2Count == 0 && cc2Count2 == 3);

    constexpr auto cc3Count = cc3.count('a');
    constexpr auto cc3Count2 = cc3.count('1');
    static_assert(cc3Count == 0 && cc3Count2 == 1);

    constexpr auto cc4Count = cc4.count('a');
    constexpr auto cc4Count2 = cc4.count('1');
    static_assert(cc4Count == 0 && cc4Count2 == 1);

    static_assert(cc4 == cc3);
    static_assert(!(cc4 != cc3));
    static_assert(cc4 != cc2 && cc2 != def);
    static_assert(cc4.count_if([](const char a_Char)
                               {
                                   return (static_cast<int>(a_Char - '0') % 2) == 0;
                               }));

    constexpr auto countIf = cc1.count_if([](const char a_Char)
                                          {
                                              return a_Char == 'T' || a_Char == 't';
                                          });
    static_assert(countIf == 3);

    constexpr auto cc3Array = cc3.to_array<cc3.size()>();
    static_assert(cc3Array.size() == cc3.size() + 1u /* +1 because array have '\0' on last element*/);
    static_assert(cc3Array[0] == cc3[0]);
    static_assert(cc3Array[1] == cc3[1]);
    static_assert(cc3Array[2] == cc3.at(2));
    static_assert(cc3Array[3] == cc3.at(3));

    constexpr const_char cc5("String create in argument!");
    static_assert(cc5.size() == 26);
    static_assert(cc5.count('!') == 1);
    static_assert(cc5.count('a') == 2);

    return 0;
}
