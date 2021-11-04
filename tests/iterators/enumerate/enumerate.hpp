#ifndef TESTS_ENUMERATE_HPP
#define TESTS_ENUMERATE_HPP

#include "babel.hpp"

namespace TESTING{
    void ENUMERATE_ITERATOR()
    {
        {
            std::list<std::string> lit = {"test", "tu", "test2"};
            std::vector<int> vit = {3, 8, 12, 5, 3, 4, 5};
            auto en = babel::ITERATOR::enumerate(vit.begin());
            auto f = *en;
            assert(f.get_index() == 0 && f.get_value() == 3);
            f.get_value() = 15;
            assert(f.get_value() == 15 && vit[0] == 15);
            ++en;
            assert(( *en ).get_index() == 1 && ( *en ).get_value() == 8);
            en++;
            assert(( *en ).get_index() == 2 && ( *en ).get_value() == 12);
            --en;
            assert(( *en ).get_index() == 1 && ( *en ).get_value() == 8);
            en--;
            assert(( *en ).get_index() == 0 && ( *en ).get_value() == 15);
            babel::ITERATOR::enumerate<decltype(vit.begin())>::value_type t = *en;
            assert(t.get_index() == 0 && t.get_value() == 15);
            int64_t good = 0;
            std::for_each(babel::ITERATOR::enumerate(vit.begin()), babel::ITERATOR::enumerate(vit.end()),
                          [&good](const auto &data) mutable {
                              assert(good == data.first());
                              ++good;
                          });
            good = 10;
            std::for_each(babel::ITERATOR::enumerate(lit.begin(), good), babel::ITERATOR::enumerate(lit.end(), good),
                          [&good](const auto &data) mutable {
                              assert(good == data.first());
                              ++good;
                          });
            good = 10;
            std::for_each(babel::ITERATOR::enumerate<decltype(lit.begin()), std::minus<>>(lit.begin(), good),
                          babel::ITERATOR::enumerate<decltype(lit.begin()), std::minus<>>(lit.end(), good),
                          [&good](const auto &data) mutable {
                              assert(good == data.first());
                              --good;
                          });
        }
        {
            std::vector<std::string> stt = {"Test1", "Test2", "Test3"};
            auto Enum = babel::ITERATOR::enumerator(stt);
            long long i = 0;
            for ( const auto &data : Enum )
            {
                assert(i++ == data.first());//NOLINT
            }
            i = 25;
            std::for_each(Enum.begin(25), Enum.end(),
                          [&i](auto Data) mutable {
                              assert(Data.first() == i++); //NOLINT
                          });
        }
        {
            std::vector<std::string> stt = {"Test1", "Test2", "Test3"};
            auto beg = babel::ITERATOR::enumerate(stt.begin());
            auto end = babel::ITERATOR::enumerate(stt.end());
            while ( beg != end )
            {
                ( *beg ).second() = "CHANGED";
                ++beg;
            }
            for ( const auto &SS: stt )
            {
                assert(SS == "CHANGED");
            }

        }
        {
            const std::vector<std::string> stt = {"Test1", "Test2", "Test3"};
            auto Enum = babel::ITERATOR::enumerator(stt);
            long long i = 0;
            for ( const auto &data : Enum )
            {
                assert(i++ == data.first());//NOLINT
            }
            i = 25;
            std::for_each(Enum.begin(25), Enum.end(),
                          [&i](auto Data) mutable {
                              assert(Data.first() == i++); //NOLINT
                          });
        }
        {
            std::vector<std::string> stt = {"Test1", "Test2", "Test3"};
            auto Enum = babel::ITERATOR::enumerator(stt);
            for ( auto data : Enum )
            {
                data.second() = "CHANGED";
            }
            for ( const auto &CH :stt )
            {
                assert(CH == "CHANGED");
            }
        }

    }
}

#endif // TESTS_ENUMERATE_HPP
