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

    //constexpr test (only static_assert)
    constexpr const char* d1 = "TestConstexpr";  // 13
    constexpr const char* d2 = "VeryLongTextVeryLongTextVeryLongText";  // 36
    constexpr const char* d3 = "1234";  // 4

    constexpr const_char ccEmpty(""); // no
    constexpr const_char def; // no
    constexpr const_char cc1(d1);  // d1
    constexpr const_char cc2(d2);  // d2
    constexpr const_char cc3(d3); // d3
    constexpr const_char cc4(cc3); // d3
    constexpr const_char ccSpace("With space");

    // Test count, size, cast to std::array
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

    // Test valid and empty

    constexpr auto cc3IsValid = cc3.is_valid();
    constexpr auto defIsValid = def.is_valid();
    static_assert(cc3IsValid && !defIsValid);
    static_assert(ccEmpty.is_empty() && def.is_empty() && !cc3.is_empty());

    // Test find

    constexpr auto cc3Found1 = cc3.find('3');
    constexpr auto cc3Found2 = cc3.find('9');
    constexpr auto defFound = cc3.find('A');
    static_assert(cc3Found1 && !cc3Found2 && !defFound);
    constexpr auto cc3FoundIf1 = cc3.find_if([](const char D)
                                             {
                                                 return static_cast<int>(D-'0') % 2 == 0;
                                             });

    constexpr auto cc3FoundIf2 = cc3.find_if([](const char D)
                                             {
                                                 return static_cast<int>(D-'0') >= 5;
                                             });

    static_assert(cc3FoundIf1 && !cc3FoundIf2);

    // Test conaints
    static_assert(cc3.contains("1234"));
    static_assert(!cc3.contains("12345"));
    static_assert(cc3.contains("4"));
    static_assert(!cc3.contains("45"));

    static_assert(!def.contains("45"));
    static_assert(!def.contains("a"));
    static_assert(def.contains(""));

    static_assert(ccEmpty.contains(""));
    static_assert(!ccEmpty.contains("a"));

    static_assert(ccSpace.contains(""));
    static_assert(ccSpace.contains(" "));
    static_assert(ccSpace.contains(" space"));
    static_assert(ccSpace.contains("space"));
    static_assert(ccSpace.contains("With space"));
    static_assert(!ccSpace.contains("with space"));
    static_assert(!ccSpace.contains("With spaced"));

    // Test to_int32_t
    {
        // Base 10
        {
            constexpr const_char case1("124");
            constexpr const_char case2("-124");
            constexpr const_char case3("-124.8");
            constexpr const_char case4("124.8");
            constexpr const_char case5("124.8fdsgs");
            constexpr const_char case6("-124.8fdsgs");
            constexpr const_char case7("22afs");
            constexpr const_char case8("-22afs");
            constexpr const_char case9("-0");
            constexpr const_char case10("0");
            constexpr const_char case11("025");
            constexpr const_char case12("-025");
            constexpr const_char caseI64Max("9223372036854775807");
            constexpr const_char caseI64MaxOutOfRange("9223372036854775808");
            constexpr const_char caseI64Min("-9223372036854775808");
            constexpr const_char caseI64MinOutOfRange("-9223372036854775809");

            static_assert(cc3.to_int64() == 1234); // cc3 case
            static_assert(case1.to_int64() == 124); // case 1
            static_assert(case2.to_int64() == -124); // case 2
            static_assert(case3.to_int64() == -124); // case 3
            static_assert(case4.to_int64() == 124); // case 4
            static_assert(case5.to_int64() == 124); // case 5
            static_assert(case6.to_int64() == -124); // case 6
            static_assert(case7.to_int64() == 22); // case 7
            static_assert(case8.to_int64() == -22); // case 8
            static_assert(case9.to_int64() == 0); // case 9
            static_assert(case10.to_int64() == 0); // case 9
            static_assert(case11.to_int64() == 25); // case 9
            static_assert(case12.to_int64() == -25); // case 9
            static_assert(caseI64Max.to_int64() == std::numeric_limits<int64_t>::max()); // case MAX
            static_assert(caseI64Min.to_int64() == std::numeric_limits<int64_t>::min()); // case MIN
            //static_assert(caseI64MaxOutOfRange.to_int64() == std::numeric_limits<int64_t>::max()); // case 2
            //static_assert(caseI64MinOutOfRange.to_int64() == std::numeric_limits<int64_t>::min()); // case 2
        }
        // Base 16
        {
            constexpr const_char case1("0x7c");
            constexpr const_char case1a("7c");
            constexpr const_char case2("-0x7C");
            constexpr const_char case2a("-7C");
            constexpr const_char case3("-7c.8");
            constexpr const_char case3a("-0x7c.8");
            constexpr const_char case4("0x7c.8");
            constexpr const_char case4a("7c.8");
            constexpr const_char case5("7c.8fdsgs");
            constexpr const_char case5a("0x7c.8fdsgs");
            constexpr const_char case6("-0x7c.8fdsgs");
            constexpr const_char case6a("-7c.8fdsgs");
            constexpr const_char case7("16kafs");
            constexpr const_char case7a("0x16kafs");
            constexpr const_char case8("-0x16kafs");
            constexpr const_char case8a("-16kafs");
            constexpr const_char case9("-0x0");
            constexpr const_char case9a("-0");
            constexpr const_char case10("0");
            constexpr const_char case10a("0x0000");
            constexpr const_char case11("0x019");
            constexpr const_char case11a("019");
            constexpr const_char case12("-0x019");
            constexpr const_char case12a("-019");
            constexpr const_char caseI64Max("7fffffffffffffff");
            constexpr const_char caseI64Maxa("0x7fffffffffffffff");
            constexpr const_char caseI64MaxOutOfRange("8000000000000000");
            constexpr const_char caseI64MaxOutOfRangea("0x8000000000000000");

            constexpr const_char caseI64Min("-8000000000000000");
            constexpr const_char caseI64Mina("-0x8000000000000000");
            constexpr const_char caseI64MinOutOfRange("-8000000000000001");
            constexpr const_char caseI64MinOutOfRangea("-0x8000000000000001");

            static_assert(case1.to_int64(16) == 124); // case 1
            static_assert(case1a.to_int64(16) == 124); // case 1a
            static_assert(case2.to_int64(16) == -124); // case 2
            static_assert(case2a.to_int64(16) == -124); // case 2a
            static_assert(case3.to_int64(16) == -124); // case 3
            static_assert(case3a.to_int64(16) == -124); // case 3a
            static_assert(case4.to_int64(16) == 124); // case 4
            static_assert(case4a.to_int64(16) == 124); // case 4a
            static_assert(case5.to_int64(16) == 124); // case 5
            static_assert(case5a.to_int64(16) == 124); // case 5a
            static_assert(case6.to_int64(16) == -124); // case 6
            static_assert(case6.to_int64(16) == -124); // case 6a
            static_assert(case7.to_int64(16) == 22); // case 7
            static_assert(case7a.to_int64(16) == 22); // case 7a
            static_assert(case8.to_int64(16) == -22); // case 8
            static_assert(case8a.to_int64(16) == -22); // case 8a
            static_assert(case9.to_int64(16) == 0); // case 9
            static_assert(case9a.to_int64(16) == 0); // case 9a
            static_assert(case10.to_int64(16) == 0); // case 10
            static_assert(case10a.to_int64(16) == 0); // case 10a
            static_assert(case11.to_int64(16) == 25); // case 11
            static_assert(case11a.to_int64(16) == 25); // case 11a
            static_assert(case12.to_int64(16) == -25); // case 12
            static_assert(case12a.to_int64(16) == -25); // case 12a
            static_assert(caseI64Max.to_int64(16) == std::numeric_limits<int64_t>::max()); // case MAX
            static_assert(caseI64Maxa.to_int64(16) == std::numeric_limits<int64_t>::max()); // case MAXa
            static_assert(caseI64Min.to_int64(16) == std::numeric_limits<int64_t>::min()); // case MIN
            static_assert(caseI64Mina.to_int64(16) == std::numeric_limits<int64_t>::min()); // case MINa
            //static_assert(caseI64MaxOutOfRange.to_int64(16) == std::numeric_limits<int64_t>::max()); // case 2
            //static_assert(caseI64MaxOutOfRangea.to_int64(16) == std::numeric_limits<int64_t>::max()); // case 2
            //static_assert(caseI64MinOutOfRange.to_int64(16) == std::numeric_limits<int64_t>::min()); // case 2
            //static_assert(caseI64MinOutOfRangea.to_int64(16) == std::numeric_limits<int64_t>::min()); // case 2
        }
        // Base 8

        // Base 2
    }
    return 0;
}
