#ifndef TESTS_RANGE_HPP
#define TESTS_RANGE_HPP

#include "babel.hpp"

namespace TESTING{
    void RANGES_ITERATOR()
    {
        {
            const auto Ranges = babel::ITERATOR::range(0, 10, 1);
            int64_t index = 0;
            std::for_each(Ranges.begin(), Ranges.end(),
                          [&index](const auto &Data) mutable {
                              assert(index == Data);
                              ++index;
                          });
        }
        {
            auto Ranges = babel::ITERATOR::range(0, 10, 1);
            auto Ranges1 = babel::ITERATOR::range(0, 9, 2);
            auto Ranges2 = babel::ITERATOR::range(0, 10, 4);
            auto Ranges3 = babel::ITERATOR::range(0, -10, 1);
            auto Ranges4 = babel::ITERATOR::range(0, -10, -2);
            auto Ranges5 = babel::ITERATOR::range(0, -10, -4);
            int64_t index = 0;
            std::for_each(Ranges.begin(), Ranges.end(),
                          [&index](const auto &Data) mutable {
                              assert(index == Data);
                              ++index;
                          });
            assert(index == 10);
            index = 0;
            std::for_each(Ranges1.begin(), Ranges1.end(),
                          [&index](const auto &Data) mutable {
                              assert(index == Data);
                              index += 2;
                          });
            assert(index == 10);
            index = 0;
            std::for_each(Ranges2.begin(), Ranges2.end(),
                          [&index](const auto &Data) mutable {
                              assert(index == Data);
                              index += 4;
                          });
            assert(index == 12);
            index = 0;
            std::for_each(Ranges3.begin(), Ranges3.end(),
                          [&index](const auto &Data) mutable {
                              assert(index == Data);
                              --index;
                          });
            assert(index == -10);
            index = 0;
            std::for_each(Ranges4.begin(), Ranges4.end(),
                          [&index](const auto &Data) mutable {
                              assert(index == Data);
                              index -= 2;
                          });
            assert(index == -10);
            index = 0;
            std::for_each(Ranges5.begin(), Ranges5.end(),
                          [&index](const auto &Data) mutable {
                              assert(index == Data);
                              index -= 4;
                          });
            assert(index == -12);
        }
        {
            long long correct = 5;
            for ( auto range : babel::ITERATOR::range(5, 15) )
            {
                assert(correct == range);
                ++correct;
            }
        }
    }
}

#endif  // TESTS_RANGE_HPP
