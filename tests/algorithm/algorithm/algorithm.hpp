#ifndef TESTS_ALGORITHM_HPP
#define TESTS_ALGORITHM_HPP

#include "babel.hpp"
#include <cassert>
#include <list>

namespace TESTING{
    void ALGORITHM_HPP() // DONE
    {
        std::string INT = "-32";
        std::string UINT = "33";
        std::string DOUBLE = "33.03";
        auto i = babel::ALGO::CAST::string_to<int>(INT);
        auto ui = babel::ALGO::CAST::string_to<unsigned int>(UINT);
        auto d = babel::ALGO::CAST::string_to<double>(DOUBLE);
        assert(i == -32 && ui == 33 && d > 33.029 && d < 33.031);
        assert(babel::ALGO::MATH::abs(-5) == 5);
        std::vector<int> p = {-3, 2, 1, -5, 3};
        babel::ALGO::MATH::abs(p);
        for ( auto el : p )
            assert (el >= 0);
        assert(babel::ALGO::VECTOR::count(p, 3) == 2);
        assert(babel::ALGO::VECTOR::count_if(p, [](int g) { return g <= 2; }) == 2);
        auto mm = babel::ALGO::VECTOR::find_min_max(p);
        assert(mm.first == 1 && mm.second == 5);
        assert(babel::ALGO::VECTOR::mean(p) == 2);
        std::vector<double> pd = {3, 2, 1, 5, 3};
        babel::ALGO::VECTOR::normalize(pd);
        for ( auto data : pd )
            assert(data >= 0.0 && data <= 1.0);
        assert(babel::ALGO::VECTOR::sum(p) == 14);
        assert(babel::ALGO::VECTOR::closest_to_mean(p) == 2);
        auto fft = babel::ALGO::MATH::FFT(pd);
        (void) fft;
        int temp = -3;
        auto temp2 = babel::ALGO::CAST::signed_unsigned_conv(temp);
        assert (!std::is_signed_v<decltype(temp2)>);
        std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7};
        auto v1 = babel::ALGO::VECTOR::drop<std::vector<int>>(v, 3);
        for ( size_t j = 0 ; j < v1.size() ; ++j )
            assert(v1[j] == static_cast<int64_t>(j + 3));
        v1 = babel::ALGO::VECTOR::drop(v, 300);
        assert(v1.empty());
        v1 = babel::ALGO::VECTOR::take<std::vector<int>>(v, 3);
        for ( size_t j = 0 ; j < v1.size() ; ++j )
            assert(v1[j] == static_cast<int64_t>(j));
        v1 = babel::ALGO::VECTOR::take(v, 300);
        for ( size_t j = 0 ; j < v1.size() ; ++j )
            assert(v1[j] == static_cast<int64_t>(j));
        assert(v1.size() == v.size() && v1 == v);

        v1 = babel::ALGO::VECTOR::repeat(v, 3);
        for ( int j = 0 ; j < 3 ; ++j )
            assert(std::vector<int>(v1.begin() + j * 8, v1.begin() + 8 * ( j + 1 )) == v);
        v1 = babel::ALGO::VECTOR::stride(v, 3);
        assert(v1.size() == 3 && v1[0] == 0 && v1[1] == 3 && v1[2] == 6);
        v.push_back(8);
        v1 = babel::ALGO::VECTOR::stride(v, 3);
        assert(v1.size() == 3 && v1[0] == 0 && v1[1] == 3 && v1[2] == 6);
        v.push_back(9);
        v1 = babel::ALGO::VECTOR::stride(v, 3);
        assert(v1.size() == 4 && v1[0] == 0 && v1[1] == 3 && v1[2] == 6 && v1[3] == 9);
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v = {0, 1, 2, 3, 4, 5, 6};
        v1 = babel::ALGO::VECTOR::stride(v, 3);
        assert(v1.size() == 3 && v1[0] == 0 && v1[1] == 3 && v1[2] == 6);
        v = {0, 1, 2, 3, 4, 5};
        v1 = babel::ALGO::VECTOR::stride(v, 3);
        assert(v1.size() == 2 && v1[0] == 0 && v1[1] == 3);
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v1 = babel::ALGO::VECTOR::stride(v, 1);
        for ( size_t j = 0 ; j < v1.size() ; ++j )
            assert(v[j] == v1[j]);
        v1 = babel::ALGO::VECTOR::stride(v, 2);
        assert(v1.size() == 4 && v1[0] == 0 && v1[3] == 6);
        v.push_back(8);
        v1 = babel::ALGO::VECTOR::stride(v, 2);
        assert(v1.size() == 5 && v1[0] == 0 && v1[4] == 8);
        v.pop_back();
        v.pop_back();
        v1 = babel::ALGO::VECTOR::stride(v, 2);
        assert(v1.size() == 4 && v1[0] == 0 && v1[3] == 6);
        v.pop_back();
        v1 = babel::ALGO::VECTOR::stride(v, 2);
        assert(v1.size() == 3 && v1[0] == 0 && v1[2] == 4);
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v1 = babel::ALGO::VECTOR::stride(v, 5);
        assert(v1.size() == 2 && v1[1] == 5);
        v1 = babel::ALGO::VECTOR::stride(v, 10);
        assert(v1.size() == 1 && v1[0] == 0);
        v1 = babel::ALGO::VECTOR::stride(v, 4);
        assert(v1.size() == 2 && v1[1] == 4);


        v.clear();
        babel::ALGO::MATH::random_generator rg;
        auto s = rg.generate<std::size_t>(5, 1006);

        auto step = rg.generate<std::size_t>(1, 101);

        for ( size_t j = 0 ; j < s ; ++j )
            v.emplace_back(rg.generate<std::size_t>(1, 101));
        v1 = babel::ALGO::VECTOR::stride(v, step);
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v1 = babel::ALGO::VECTOR::drop_idx(v, 2);
        for ( size_t j = 0 ; j < 2 ; ++j )
            assert(v1[j] == static_cast<int64_t>(j));
        for ( size_t j = 2 ; j < v1.size() ; ++j )
            assert(v1[j] == static_cast<int64_t>(j + 1));
        assert(v1.size() + 1 == v.size());
        v = { };
        v1 = babel::ALGO::VECTOR::drop_idx(v, 2);
        assert(v1.empty());
        v = {5};
        v1 = babel::ALGO::VECTOR::drop_idx(v, 2);
        assert(v1.size() == 1 && v1[0] == 5);
        v1 = babel::ALGO::VECTOR::drop_idx(v, 0);
        assert(v1.empty());
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v1 = babel::ALGO::VECTOR::drop_last<std::vector<int>>(v, 3);
        assert(v1.size() == 5);
        for ( size_t j = 0 ; j < v1.size() ; ++j )
            assert(v1[j] == static_cast<int64_t>(j));
        v = {1};
        v1 = babel::ALGO::VECTOR::drop_last(v, 0);
        assert(v1.size() == 1 && v1[0] == 1);
        v1 = babel::ALGO::VECTOR::drop_last(v, 1);
        assert(v1.empty());
        v1 = babel::ALGO::VECTOR::drop_last(v, 1);
        assert(v1.empty());
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v1 = babel::ALGO::VECTOR::take_last<std::vector<int>>(v, 3);
        assert(v1.size() == 3 && v1[0] == 5 && v1[1] == 6 && v1[2] == 7);
        v = {0, 1};
        v1 = babel::ALGO::VECTOR::take_cyclic(v, 4);
        assert(v1.size() == 4 && v1[0] == 0 && v1[1] == 1 && v1[2] == 0 && v1[3] == 1);
        v1 = babel::ALGO::VECTOR::take_cyclic(v, 5);
        assert(v1.size() == 5 && v1[0] == 0 && v1[1] == 1 && v1[2] == 0 && v1[3] == 1 && v1[4] == 0);
        v = {1, 2};
        v1 = babel::ALGO::VECTOR::replicate_elems(v, 3);
        v = {1, 1, 1, 2, 2, 2};
        assert(v1.size() == 6 && v == v1);
        v = {1, 2};
        v1 = babel::ALGO::VECTOR::replicate_elems(v, 4);
        v = {1, 1, 1, 1, 2, 2, 2, 2};
        assert(v1.size() == 8 && v == v1);
        auto v2 = babel::ALGO::VECTOR::enumerate(v);
        assert(v2.size() == v.size());
        for ( size_t j = 0 ; j < v.size() ; ++j )
            assert(v2[j].first == j && v2[j].second == v[j]);
        v2 = babel::ALGO::VECTOR::run_length_encode(v);
        assert(v2.size() == 2);
        assert(v2[0].first == 4 && v2[0].second == 1 && v2[1].first == 4 && v2[1].second == 2);
        v = {1, 1, 1, 1, 2, 2, 2, 2, 3};
        v2 = babel::ALGO::VECTOR::run_length_encode(v);
        assert(v2.size() == 3);
        assert(v2[0].first == 4 && v2[0].second == 1 && v2[1].first == 4 && v2[1].second == 2 && v2[2].first == 1 &&
               v2[2].second == 3);
        v = { };
        v2 = babel::ALGO::VECTOR::run_length_encode(v);
        assert(v2.empty());
        v2 = babel::ALGO::VECTOR::enumerate(v);
        assert(v2.empty());
        auto zeros = babel::ALGO::VECTOR::zeros(3, 2);
        assert(zeros.size() == 3 && zeros[0].size() == 2 && zeros[0][0] == 0);
        auto zeros1 = babel::ALGO::VECTOR::zeros(4);
        assert(zeros1.size() == 4 && zeros1[3] == 0);
        auto ones = babel::ALGO::VECTOR::ones(3, 2);
        assert(ones.size() == 3 && ones[0].size() == 2 && ones[0][0] == 1);
        auto ones1 = babel::ALGO::VECTOR::ones(4);
        assert(ones1.size() == 4 && ones1[3] == 1);
        float f = 3.14f;
        auto astype = babel::ALGO::CAST::asType<int>(f);
        assert(astype == 3);
        astype = 213;
        auto astypestr = babel::ALGO::CAST::asType<std::string>(astype);
        auto astypeint = babel::ALGO::CAST::asType<int32_t>(astypestr);
        assert(astypeint == 213);
        {
            struct P
            {
                int x = 2;

                virtual void del()
                { }
            };
            struct Y : public P
            {
                int z = 2;

                void del() override
                {

                }
            };
            Y y;
            y.x = 4;
            y.z = 12;
            auto z = babel::ALGO::CAST::asType<P *>(y);
            auto z1 = babel::ALGO::CAST::asType<P *>(&y);
            assert(z->x == 4 && z1->x == 4);
            auto z2 = babel::ALGO::CAST::asType<Y *>(z);
            auto z3 = babel::ALGO::CAST::asType<Y *>(z1);
            assert(z2->x == 4 && z3->x == 4);
            assert(z2->z == 12 && z3->z == 12);
            auto z4 = babel::ALGO::CAST::asType<P *>(z2);
            auto z5 = babel::ALGO::CAST::asType<P *>(z3);
            assert(z4->x == 4 && z5->x == 4);

            std::vector<int> vtype = {3, 1, 2};
            std::list<float> ltype;
            ltype = babel::ALGO::CAST::asType<decltype(ltype)>(vtype);

            {
                Y yy;
                yy.z = 25;
                yy.x = 12;
                P *pp = babel::ALGO::CAST::asType<P *>(yy);
                P *pp1 = babel::ALGO::CAST::asType<P *>(&yy);
                assert(pp->x == 12);
                assert(pp1->x == 12);
                yy.x = 30;
                assert(pp->x == 30);
                assert(pp1->x == 30);
                auto &org = babel::ALGO::CAST::asType<Y &>(*pp);
                yy.z = 222;
                yy.x = 15;
                assert(pp->x == 15);
                assert(pp1->x == 15);
                assert(org.x == 15 && org.z == 222);
                org.x = 10;
                assert(pp->x == 10 && yy.x == 10);
                assert(pp1->x == 10);
            }

            std::list<float> ltype1 = {1.f, 2.f, 3.f};
            std::vector<int> vtype1;
            vtype1 = babel::ALGO::CAST::asType<decltype(vtype1)>(ltype1);

            assert(vtype1[0] == 1 && vtype1[1] == 2 && vtype1[2] == 3);
            auto bltype = ltype.begin();
            assert(*bltype == 3);
            ++bltype;
            assert(*bltype == 1);
            ++bltype;
            assert(*bltype == 2);

            std::vector<std::string> ts = {"3", "1", "5"};
            std::vector<int> ti;
            ti = babel::ALGO::CAST::asType<decltype(ti)>(ts);


            std::vector<int> ti1 = {1, 2, 3};
            std::vector<std::string> ts1;
            ts1 = babel::ALGO::CAST::asType<decltype(ts1)>(ti1);

            std::vector<int> ti2 = {1, 2, 3};
            std::vector<std::string> ts2;
            ts2 = babel::ALGO::CAST::asType<decltype(ts2)>(ti2, [](int) -> std::string { return "str"; });
            for ( const auto &TS2 : ts2 )
                assert(TS2 == "str");

            int pp = 4;
            auto &pp1 = babel::ALGO::CAST::asType<int &>(pp);
            assert(pp == 4 && pp1 == 4);
            pp = 25;
            assert(pp == 25 && pp1 == 25);
            {
                std::vector<std::string> sv = {"t1", "t2", "t3"};
                std::list<std::string> sl;
                sl = babel::ALGO::CAST::asType<decltype(sl)>(sv);
                auto beg = sl.begin();
                assert(sv[0] == "t1" && sv[1] == "t2" && sv[2] == "t3");
                assert(*beg == "t1");
                ++beg;
                assert(*beg == "t2");
                ++beg;
                assert(*beg == "t3");
            }
            {
                std::vector<std::string> sv = {"t1", "t2", "t3"};
                std::list<std::string> sl;

                sl = babel::ALGO::CAST::asType<decltype(sl)>(std::move(sv));
                auto beg = sl.begin();
                assert(sv[0].empty() && sv[1].empty() && sv[2].empty()); //NOLINT
                assert(*beg == "t1");
                ++beg;
                assert(*beg == "t2");
                ++beg;
                assert(*beg == "t3");
            }


            assert(ti[0] == 3 && ti[1] == 1 && ti[2] == 5);
            assert(ts[0] == "3" && ts[1] == "1" && ts[2] == "5");
            assert(ts1[0] == "1" && ts1[1] == "2" && ts1[2] == "3");
            assert(ti1[0] == 1 && ti1[1] == 2 && ti1[2] == 3);

            auto lambda = [](int pt) -> std::unique_ptr<std::string> {
                return std::make_unique<std::string>(std::to_string(pt * pt));
            };
            int xlamb = 2;
            auto ylamb = babel::ALGO::CAST::asType<std::unique_ptr<std::string>>(xlamb, lambda);
            assert(xlamb == 2 && *ylamb == std::to_string(xlamb * xlamb));
            auto PXP = babel::ALGO::CAST::asType<int>(std::string("25"),
                                                      [](const std::string &) -> int { return 555; });
            assert(PXP == 555);
            PXP = babel::ALGO::CAST::asType<int>(std::string("25"));
            assert(PXP == 25);
            auto l1 = [](const std::vector<std::string> &vec) -> std::vector<int> {
                int suma = 0;
                for ( const auto &El : vec )
                {
                    suma += babel::ALGO::CAST::string_to<int>(El);
                }
                return {suma};
            };
            auto l2 = [](const std::string &Str) -> int {
                return babel::ALGO::CAST::string_to<int>(Str) * 10;
            };
            std::vector<std::string> pps = {"1", "2"};
            std::vector<int> vv, vv1;
            vv = babel::ALGO::CAST::asType<decltype(vv)>(pps, l1);
            assert(vv.size() == 1 && vv[0] == 3);

            vv1 = babel::ALGO::CAST::asType<decltype(vv1)>(pps, l2);
            assert(vv1.size() == 2 && vv1[0] == 10 && vv1[1] == 20);

            std::string st1 = "test";
            auto st2 = babel::ALGO::CAST::asType<std::string>(std::move(st1));
            assert(st1.empty() && st2 == "test"); //NOLINT
            st1 = babel::ALGO::CAST::asType<std::string>(st2);
            assert(st1 == "test" && st2 == "test");
        }
    }
}

#endif  // TESTS_ALGORITHM_HPP
