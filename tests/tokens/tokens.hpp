#ifndef TESTS_TOKENS_HPP
#define TESTS_TOKENS_HPP

#include "babel.hpp"

namespace TESTING{
    void TOKENS_HPP()
    {
        babel::TOKEN::tokenizer tokens(5);
        auto sum_vec = [&](int64_t &sum, std::size_t &pos, const std::vector<int> &num) mutable {
            while ( pos < num.size() )
            {
                auto Token = tokens.get_token(0);
                (void) Token;
                if ( pos >= num.size() )
                {
                    break;
                }
                sum += num[pos];
                ++pos;
            }
        };
        babel::ALGO::MATH::random_generator rg;
        for ( int ik = 0 ; ik < 5 ; ++ik )
        {
            std::vector<int> to_sum(10000);
            for ( auto &Element : to_sum )
            {
                Element = rg.generate<int>(-500, 500);
            }
            int64_t sum = std::accumulate(to_sum.begin(), to_sum.end(), 0);
            std::vector<std::thread> vec;
            std::size_t i = 0;
            int64_t sum_token = 0;
            for ( std::size_t j = 0 ; j < 10 ; ++j )
            {
                vec.emplace_back(sum_vec, std::ref(sum_token), std::ref(i), std::ref(to_sum));
            }
            for ( auto &th : vec )
                th.join();
            assert(sum == sum_token);
        }

    }
}

#endif // TESTS_TOKENS_HPP
