#ifndef TESTS_DYNAMIC_ARRAY_HPP
#define TESTS_DYNAMIC_ARRAY_HPP

#include "babel.hpp"

namespace TESTING{
    void DYNAMIC_ARRAY_HPP()
    {
        {
            babel::CONTAINER::dynamic_array<int> x;
            x.push_back(1);
            assert(x.size() == 1 && x[0] == 1);
            x.push_back(2);
            assert(x.size() == 2 && x[0] == 1 && x[1] == 2);
            x.push_back(3);
            assert(x.size() == 3 && x[0] == 1 && x[1] == 2 && x[2] == 3);
            x.clear();
            assert(x.size() == 0);
            x.push_back(1);
            x.push_back(2);
            x.push_back(3);
            babel::CONTAINER::dynamic_array<int> y = std::move(x);
            assert(y.size() == 3 && y[0] == 1 && y[1] == 2 && y[2] == 3);
            auto z = y;
            assert(z.size() == 3 && z[0] == 1 && z[1] == 2 && z[2] == 3);
            babel::CONTAINER::dynamic_array<int> p;
            p.push_back(12);
            p = z;
            assert(p.size() == 3 && p[0] == 1 && p[1] == 2 && p[2] == 3);
            babel::CONTAINER::dynamic_array<int> h;
            h.push_back(1);
            p = h;
            assert(p.size() == 1 && p[0] == 1);
            p.clear();
            p.push_back({3, 1, 2});
            assert(p.size() == 3 && p[0] == 3 && p[1] == 1 && p[2] == 2);
            babel::CONTAINER::dynamic_array<long long int> h1({1, 3, 5, 8});
            assert(h1.size() == 4 && h1[0] == 1 && h1[3] == 8);
            babel::CONTAINER::dynamic_array<int> h2(500, 5);
            assert(h2.size() == 500 && h2[0] == 5 && h2[499] == 5);
            for ( int pp : h2 )
                assert(pp == 5);

            babel::CONTAINER::dynamic_array<int> dd {3, 1, 5, 7};
            auto dp(dd);
            auto dk(std::move(dd));
            dd.push_back(15); //NOLINT

            assert(dd.size() == 1 && dd[0] == 15);
            assert(dp.size() == dk.size() && dp.size() == 4);
            for ( std::size_t i = 0 ; i < dp.size() ; ++i )
                assert(dp[i] == dk[i]);
        }


        float fl = 30.14f;
        babel::CONTAINER::dynamic_array<int> p;
        p.push_back(static_cast<int>(fl));
        p.clear();
        p.push_back(static_cast<int>(3.14f));
        p.push_back(static_cast<int>(fl));
        p.clear();
        p.emplace_back(fl);
        p.pop_back();
        p.push_back({31, 5, 4, 1, 8});
        auto x = p;
        assert(x.size() == p.size());
        x = std::move(p);
        assert(p.size() == 0); //NOLINT
        x.clear();
    }

}

#endif // TESTS_DYNAMIC_ARRAY_HPP
