//
// Created by Wojtek on 08.04.2021.
//

#ifndef CLIONPROJECT_TESTER_HPP
#define CLIONPROJECT_TESTER_HPP

#include "babel.hpp"
#include "cassert"

namespace TESTING{

    void WRAPER_HPP() //DONE
    {
        babel::WRAPER::wrap<int> p;
        babel::WRAPER::wrap<std::unique_ptr<int>> up;
        p.emplace(15);
        up.emplace(std::make_unique<int>(15));
        assert(p.get() == 15 && *up.get() == 15);
        assert(*p == 15 && **up == 15);
        assert(*up->get() == 15);
        babel::WRAPER::wrap<std::vector<int>> vec({3, 1, 4});
        assert(vec.size() == 3);
        vec = {4, 1, 2, 5};
        assert(vec.size() == 4);
        up = std::make_unique<int>(300);
        assert(**up == 300);
        babel::WRAPER::wrap<int> p1(15);
        babel::WRAPER::wrap<std::unique_ptr<int>> up1(std::make_unique<int>(15));
        assert(*p1 == 15 && **up1 == 15);
        babel::WRAPER::wrap<std::unique_ptr<int>> up2(std::move(up1));
        assert(**up2 == 15);
        up2 = std::move(up);
        assert(**up2 == 300);
        babel::WRAPER::wrap<std::string> st("test");
        std::string kw = "kwas";
        st = std::move(kw);
        assert(*st == "kwas");
    }

    void VARIADIC_HPP() // DONE
    {

        babel::VARIADIC::holder<int> p(3, 4, 12, 5);
        assert(p[0] == 3 && p[3] == 5);
        babel::VARIADIC::holder<int> p1(p);
        assert(p1[0] == 3 && p1[3] == 5);
        p1.get().clear();
        p = p1;
        assert(p.get().empty());
        babel::VARIADIC::holder<int> p3(15);
        assert(p3[0] == 15);
        assert(p3->at(0) == 15);
    }

    void TIME_HPP() // DONE
    {
        babel::TIME::timer t;
        t.start();
        auto p1 = t.get_time_ns();
        auto p2 = t.get_time();
        auto p3 = t.get_time_micro();
        auto p4 = t.get_time_mili();
        p1 += 5;
        p2 += static_cast<long double>(0.2);
        p3 += 5;
        p4 += 5;
        t.start();
    }

    void OPTIONAL_HPP() // DONE
    {
        babel::OPT::optional<int> p;
        assert(!p.has_value() && p.value_or(15) == 15 && !bool(p));
        p.emplace(25);
        assert(p.has_value() && p.value_or(15) == 25 && bool(p));
        p = 150;
        assert(p.value() == 150);
        babel::OPT::optional<int> p1(p);
        assert(p1.has_value() && p1.value() == 150);
        babel::OPT::optional<int> p2(25);
        babel::OPT::optional<int> p3(std::move(p1));
        assert(p2.has_value() && p2.value() == 25);
        assert(p3.has_value() && p3.value() == 150);
        p3.swap(p2);
        assert(p2.value() == 150 && p3.value() == 25);
    }

    void MUST_HAVE_HPP() //DONE
    {
        uint64_t F[2][2] = {{3, 4},
                            {5, 8}};
        _BABEL_PRIVATE_DO_NOT_USE::_PRIVATE_BABEL::babel_pow(F, 10);

    }

    void MATH_HPP() // DONE
    {
        auto compare = [](double x, double y, double blad = 0.1) -> bool {
            double x_left = x - blad;
            double x_right = x + blad;
            return x_left <= y && x_right >= y;
        };
        auto func = [](double x) { return 2.0 * x * x * x; }; // 2x^3
        //Pierwsza pochodna 6x^2 -> dla 3 = 54
        //Druga pochodna 12x -> dla 3 = 36
        using namespace babel::MATH::DERIVATIVE;
        auto f1 = FIRST::three_point(func);
        assert(compare(f1(3), 54.0));
        auto f2 = FIRST::five_point(func);
        assert(compare(f2(3), 54.0));
        auto f3 = FIRST::by_definiton(func);
        assert(compare(f3(3), 54.0));
        auto f4 = FIRST::forward(func);
        assert(compare(f4(3), 54.0));
        auto f5 = FIRST::backward(func);
        assert(compare(f5(3), 54.0));
        auto f6 = FIRST::central(func);
        assert(compare(f6(3), 54.0));
        auto f7 = SECOND::three_point(func);
        auto f8 = SECOND::five_point(func);
        assert(compare(f7(3), 36.0));
        assert(compare(f8(3), 36.0));


        assert(babel::MATH::CONSTANT::E<double> > 2.7 && babel::MATH::CONSTANT::E<double> < 2.72);
        assert(babel::MATH::CONSTANT::PI<double> > 3.140 && babel::MATH::CONSTANT::PI<double> < 3.142);
        assert(babel::MATH::CONSTANT::sqrt_2<double> > 1.40 && babel::MATH::CONSTANT::sqrt_2<double> < 1.42);
        assert(babel::MATH::CONSTANT::sqrt_3<double> > 1.731 && babel::MATH::CONSTANT::sqrt_3<double> < 1.733);
        assert(babel::MATH::CONSTANT::PLANCK<double> > 6.62607004e-35 &&
               babel::MATH::CONSTANT::PLANCK<double> < 6.62607004e-33);
        assert(babel::MATH::CONSTANT::golden_ratio<double> > 1.617 &&
               babel::MATH::CONSTANT::golden_ratio<double> < 1.619);


        assert(babel::MATH::abs(-5) == 5 && babel::MATH::abs(5) == 5);

        assert(babel::MATH::max(15, 5) == 15 && babel::MATH::max(5, 15) == 15);
        assert(babel::MATH::max(0, 13, 2, 5, 2, 20) == 20);

        assert(babel::MATH::min(15, 5) == 5 && babel::MATH::min(5, 15) == 5);
        assert(babel::MATH::min(0, 13, 2, 5, 2, 20, -1) == -1);

        std::vector<int> cont = {3, 5, 2, -1, 5, 8};

        assert(babel::MATH::max(cont) == 8 && babel::MATH::min(cont) == -1);

        assert(!babel::MATH::is_neg(5) && babel::MATH::is_neg(-5));

        assert(babel::MATH::factorial(5) == babel::MATH::factorial<5>() && babel::MATH::factorial(5) == 120);

        double d = babel::MATH::binomial_coefficient<5, 3>();
        assert(babel::MATH::binomial_coefficient(5, 3) == d);

        assert(babel::MATH::fib(4) == 3);
        assert(babel::MATH::fib(6) == 8);
        assert(compare(babel::MATH::delta(2, 4, 3), -8));
        assert(babel::MATH::square_area(3) == 9);
        assert(babel::MATH::square_circumference(3) == 12);
        assert(babel::MATH::cube_volume(4) == 64);
        assert(babel::MATH::rectangle_area(3, 2) == 6);
        assert(babel::MATH::rectangle_circumference(3, 2) == 10);
        assert(babel::MATH::cuboid_volume(2, 3, 4) == 24);
        assert(compare(babel::MATH::circle_area<double>(3), 28.26));
        assert(compare(babel::MATH::circle_area<int>(3), 27));
        assert(compare(babel::MATH::circle_circumference<double>(3), 18.84));
        assert(compare(babel::MATH::circle_circumference<int>(3), 18));
        assert(compare(babel::MATH::sphere_volume<double>(4), 267.94, 0.5));
        assert(compare(babel::MATH::sphere_volume<int>(4), 256));
        assert(compare(babel::MATH::cylinder_volume<double>(3, 8), babel::MATH::circle_area<double>(3) * 8.0));
        assert(compare(babel::MATH::cone_volume<double>(3, 2), babel::MATH::cylinder_volume<double>(3, 2) * 1.0 / 3.0));
        assert(compare(babel::MATH::kW_to_HP<double>(babel::MATH::HP_to_kW<double>(30)),
                       babel::MATH::kW_to_HP<double>(babel::MATH::HP_to_kW<double>(30))));
        assert(babel::MATH::map<double>(305, 5, 905, 0, 1) >= 0.0 &&
               babel::MATH::map<double>(305, 5, 905, 0, 1) <= 1.0);

        auto r = babel::MATH::prime_factors(64u);
        assert(r.size() == 6);
        for ( auto num : r )
            assert(num == 2);
        r = babel::MATH::prime_factors(210u);
        assert(r.size() == 4);
        assert(r[0] == 2 && r[1] == 3 && r[2] == 5 && r[3] == 7);
        r = babel::MATH::prime_factors(1155u);
        assert(r.size() == 4);
        assert(r[0] == 3 && r[1] == 5 && r[2] == 7 && r[3] == 11);
        assert(babel::MATH::gcd(24, 36) == 12);
        assert(babel::MATH::lcm(24, 36) == 72);

        assert(babel::MATH::gcd(256, 24) == 8);
        assert(babel::MATH::lcm(256, 24) == 768);

        auto fx = babel::MATH::find_x(-1.0, -11.0, 12.0);
        assert(fx.size() == 2 && fx[0] == -12 && fx[1] == 1);
        fx = babel::MATH::find_x(2.0, -4.0, 2.0);
        assert(fx.size() == 1 && fx[0] == 1);
        fx = babel::MATH::find_x(2.0, 6.0, 12.0);
        assert(fx.empty());


    }

    void FILE_SYSTEM_HPP() //DONE
    {
        std::ifstream f1("../main.cpp");
        std::ifstream f2("../babel.hpp");
        assert(f1.is_open() && f2.is_open());
        babel::FILE_SYS::close_file(f1, f2);
        assert(!f1.is_open() && !f2.is_open());
        auto files = babel::FILE_SYS::scan_folder("../babLib");
        assert(babel::FILE_SYS::file_extension(files[0]) == "hpp");
        assert(babel::FILE_SYS::file_without_extension(files[0]).find("hpp") == std::string::npos);
        assert(babel::FILE_SYS::filename_contain(files[0], "hpp"));
        //assert(babel::FILE_SYS::load_txt_to_vector("../loremipsum.txt").size() == 21600);
        //auto li = babel::FILE_SYS::load_txt("../loremipsum.txt");
        assert(babel::FILE_SYS::file_exist("../babel.hpp"));
        assert(!babel::FILE_SYS::file_exist("dhshds"));
        assert(!babel::FILE_SYS::file_exist("../cmake-build-release"));


        assert(!babel::FILE_SYS::folder_exist("../babel.hpp"));
        assert(!babel::FILE_SYS::folder_exist("dhshds"));
        assert(babel::FILE_SYS::folder_exist("../cmake-build-release"));

        assert(babel::FILE_SYS::file_folder_exist("../babel.hpp"));
        assert(!babel::FILE_SYS::file_folder_exist("dhshds"));
        assert(babel::FILE_SYS::file_folder_exist("../cmake-build-release"));
    }

    void CHAR_HPP()
    {
        using CHAR = babel::CHAR::ASCII_CHAR;
        CHAR c;
        c = 'A';
        assert(c.get() == 'A');
        c.get_by_ref() = 'B';
        assert(c.get() == 'B');
        c.set('D');
        assert(c.get() == 'D');
        assert(!c.is_number() && c.is_alphabetical() && !c.is_lower() && !c.is_space() && c.is_upper());
        c.set('a');
        assert(!c.is_number() && c.is_alphabetical() && c.is_lower() && !c.is_space() && !c.is_upper());
        c.set('5');
        assert(c.is_number() && !c.is_alphabetical() && !c.is_lower() && !c.is_space() && !c.is_upper());
        c.set(' ');
        assert(!c.is_number() && !c.is_alphabetical() && !c.is_lower() && c.is_space() && !c.is_upper());
        c.set('d');
        assert(c.to_upper() == 'D');
        c.set('D');
        assert(c.to_lower() == 'd');
        c.set('5');
        assert(c.to_int_number() == 5);
        c.set_number(6);
        assert(c.get() == '6');
    }


    void ANY_HPP_VOID_ANY() // DONE
    {
        using vid = babel::ANY::VoidAny::any;
        vid d1(15);
        vid d2(std::make_unique<int>(25));
        vid d3 = babel::ANY::VoidAny::make_any(std::make_unique<int>(33));
        vid d4;
        assert(!d4.has_value() && d3.has_value() && d2.has_value() && d1.has_value());
        d2.swap(d3);
        assert(babel::ANY::cast_any<int>(d1) == 15);
        assert(*babel::ANY::cast_any<std::unique_ptr<int>>(d2) == 33);
        assert(*babel::ANY::cast_any<std::unique_ptr<int>>(d3) == 25);
        babel::ANY::VoidAny::destroy_any<int>(d1);
        babel::ANY::VoidAny::destroy_any<std::unique_ptr<int>>(d2);
        babel::ANY::VoidAny::destroy_any<std::unique_ptr<int>>(d3);
        d4 = std::string("pies");
        babel::ANY::destroy_any<std::string>(d4);
        assert(!d4.has_value() && !d2.has_value());
        std::string t = "pies";
        auto d5 = babel::ANY::VoidAny::make_any(std::move(t));
        assert(d5.cast<std::string>() == "pies" && t == "");
        babel::ANY::destroy_any<std::string>(d5);
    }

    void ANY_HPP_POLY_ANY() // DONE
    {
        using vid = babel::ANY::PolAny::any;
        vid d1(31);
        vid d2(babel::ANY::PolAny::make_any(33));
        assert(d1.has_value() && d1.cast<int>() == 31);
        assert(d2.has_value() && d2.cast<int>() == 33);
        std::string test = "pies";
        vid d3(babel::ANY::PolAny::make_any(test));
        assert(d3.cast<std::string>() == "pies" && test == "pies");
        vid d4(babel::ANY::PolAny::make_any(std::move(test)));
        assert(d4.cast<std::string>() == "pies" && test == "");
        d4.emplace<std::string>("testowy napis");
        assert(d4.cast<std::string>() == "testowy napis");
        d3.emplace<std::string>("t2");
        assert(d4 == d3 && !d4.cmp<std::string>(d3));
        d3.reset();
        assert(d4!=d3  && !d4.cmp<std::string>(d3));
    }

    void ALGORITHM_HPP() // DONE
    {
        std::string INT = "-32";
        std::string UINT = "33";
        std::string DOUBLE = "33.03";
        auto i = babel::ALGO::string_to<int>(INT);
        auto ui = babel::ALGO::string_to<unsigned int>(UINT);
        auto d = babel::ALGO::string_to<double>(DOUBLE);
        assert(i == -32 && ui == 33 && d > 33.029 && d < 33.031);
        assert(babel::ALGO::abs(-5) == 5);
        std::vector<int> p = {-3, 2, 1, -5, 3};
        babel::ALGO::abs(p);
        for ( auto el : p )
            assert (el >= 0);
        assert(babel::ALGO::count(p, 3) == 2);
        assert(babel::ALGO::count_if(p, [](int g) { return g <= 2; }) == 2);
        auto mm = babel::ALGO::find_min_max(p);
        assert(mm.first == 1 && mm.second == 5);
        assert(babel::ALGO::mean(p) == 2);
        std::vector<double> pd = {3, 2, 1, 5, 3};
        babel::ALGO::normalize(pd);
        for ( auto data : pd )
            assert(data >= 0.0 && data <= 1.0);
        assert(babel::ALGO::sum(p) == 14);
        assert(babel::ALGO::closest_to_mean(p) == 2);
        babel::ALGO::FFT(pd);
        int temp = -3;
        auto temp2 = babel::ALGO::signed_unsigned_conv(temp);
        assert (!std::is_signed_v<decltype(temp2)>);
        std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7};
        auto v1 = babel::ALGO::drop<std::vector<int>>(v, 3);
        for ( size_t j = 0 ; j < v1.size() ; ++j )
            assert(v1[j] == static_cast<int64_t>(j + 3));
        v1 = babel::ALGO::drop(v, 300);
        assert(v1.empty());
        v1 = babel::ALGO::take<std::vector<int>>(v, 3);
        for ( size_t j = 0 ; j < v1.size() ; ++j )
            assert(v1[j] == static_cast<int64_t>(j));
        v1 = babel::ALGO::take(v, 300);
        for ( size_t j = 0 ; j < v1.size() ; ++j )
            assert(v1[j] == static_cast<int64_t>(j));
        assert(v1.size() == v.size() && v1 == v);

        v1 = babel::ALGO::repeat(v, 3);
        for ( int j = 0 ; j < 3 ; ++j )
            assert(std::vector<int>(v1.begin() + j * 8, v1.begin() + 8 * ( j + 1 )) == v);
        v1 = babel::ALGO::stride(v, 3);
        assert(v1.size() == 3 && v1[0] == 0 && v1[1] == 3 && v1[2] == 6);
        v.push_back(8);
        v1 = babel::ALGO::stride(v, 3);
        assert(v1.size() == 3 && v1[0] == 0 && v1[1] == 3 && v1[2] == 6);
        v.push_back(9);
        v1 = babel::ALGO::stride(v, 3);
        assert(v1.size() == 4 && v1[0] == 0 && v1[1] == 3 && v1[2] == 6 && v1[3] == 9);
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v = {0, 1, 2, 3, 4, 5, 6};
        v1 = babel::ALGO::stride(v, 3);
        assert(v1.size() == 3 && v1[0] == 0 && v1[1] == 3 && v1[2] == 6);
        v = {0, 1, 2, 3, 4, 5};
        v1 = babel::ALGO::stride(v, 3);
        assert(v1.size() == 2 && v1[0] == 0 && v1[1] == 3);
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v1 = babel::ALGO::stride(v, 1);
        for ( size_t j = 0 ; j < v1.size() ; ++j )
            assert(v[j] == v1[j]);
        v1 = babel::ALGO::stride(v, 2);
        assert(v1.size() == 4 && v1[0] == 0 && v1[3] == 6);
        v.push_back(8);
        v1 = babel::ALGO::stride(v, 2);
        assert(v1.size() == 5 && v1[0] == 0 && v1[4] == 8);
        v.pop_back();
        v.pop_back();
        v1 = babel::ALGO::stride(v, 2);
        assert(v1.size() == 4 && v1[0] == 0 && v1[3] == 6);
        v.pop_back();
        v1 = babel::ALGO::stride(v, 2);
        assert(v1.size() == 3 && v1[0] == 0 && v1[2] == 4);
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v1 = babel::ALGO::stride(v, 5);
        assert(v1.size() == 2 && v1[1] == 5);
        v1 = babel::ALGO::stride(v, 10);
        assert(v1.size() == 1 && v1[0] == 0);
        v1 = babel::ALGO::stride(v, 4);
        assert(v1.size() == 2 && v1[1] == 4);

        v.clear();
        auto s = static_cast<size_t>(rand() % 1000 + 5);
        auto step = static_cast<size_t>(rand() % 100 + 1);
        for ( size_t j = 0 ; j < s ; ++j )
            v.emplace_back(rand() % 100);
        v1 = babel::ALGO::stride(v, step);
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v1 = babel::ALGO::drop_idx(v, 2);
        for ( size_t j = 0 ; j < 2 ; ++j )
            assert(v1[j] == static_cast<int64_t>(j));
        for ( size_t j = 2 ; j < v1.size() ; ++j )
            assert(v1[j] == static_cast<int64_t>(j + 1));
        assert(v1.size() + 1 == v.size());
        v = { };
        v1 = babel::ALGO::drop_idx(v, 2);
        assert(v1.empty());
        v = {5};
        v1 = babel::ALGO::drop_idx(v, 2);
        assert(v1.size() == 1 && v1[0] == 5);
        v1 = babel::ALGO::drop_idx(v, 0);
        assert(v1.empty());
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v1 = babel::ALGO::drop_last<std::vector<int>>(v, 3);
        assert(v1.size() == 5);
        for ( size_t j = 0 ; j < v1.size() ; ++j )
            assert(v1[j] == static_cast<int64_t>(j));
        v = {1};
        v1 = babel::ALGO::drop_last(v, 0);
        assert(v1.size() == 1 && v1[0] == 1);
        v1 = babel::ALGO::drop_last(v, 1);
        assert(v1.empty());
        v1 = babel::ALGO::drop_last(v, 1);
        assert(v1.empty());
        v = {0, 1, 2, 3, 4, 5, 6, 7};
        v1 = babel::ALGO::take_last<std::vector<int>>(v, 3);
        assert(v1.size() == 3 && v1[0] == 5 && v1[1] == 6 && v1[2] == 7);
        v = {0, 1};
        v1 = babel::ALGO::take_cyclic(v, 4);
        assert(v1.size() == 4 && v1[0] == 0 && v1[1] == 1 && v1[2] == 0 && v1[3] == 1);
        v1 = babel::ALGO::take_cyclic(v, 5);
        assert(v1.size() == 5 && v1[0] == 0 && v1[1] == 1 && v1[2] == 0 && v1[3] == 1 && v1[4] == 0);
        v = {1, 2};
        v1 = babel::ALGO::replicate_elems(v, 3);
        v = {1, 1, 1, 2, 2, 2};
        assert(v1.size() == 6 && v == v1);
        v = {1, 2};
        v1 = babel::ALGO::replicate_elems(v, 4);
        v = {1, 1, 1, 1, 2, 2, 2, 2};
        assert(v1.size() == 8 && v == v1);
        auto v2 = babel::ALGO::enumerate(v);
        assert(v2.size() == v.size());
        for ( size_t j = 0 ; j < v.size() ; ++j )
            assert(v2[j].first == j && v2[j].second == v[j]);
        v2 = babel::ALGO::run_length_encode(v);
        assert(v2.size() == 2);
        assert(v2[0].first == 4 && v2[0].second == 1 && v2[1].first == 4 && v2[1].second == 2);
        v = {1, 1, 1, 1, 2, 2, 2, 2, 3};
        v2 = babel::ALGO::run_length_encode(v);
        assert(v2.size() == 3);
        assert(v2[0].first == 4 && v2[0].second == 1 && v2[1].first == 4 && v2[1].second == 2 && v2[2].first == 1 &&
               v2[2].second == 3);
        v = { };
        v2 = babel::ALGO::run_length_encode(v);
        assert(v2.empty());
        v2 = babel::ALGO::enumerate(v);
        assert(v2.empty());

        auto vr = babel::ALGO::range(3);
        assert(vr.size() == 3 && vr[0] == 0 && vr[2] == 2);
        vr = babel::ALGO::range(-3);
        assert(vr.size() == 3 && vr[0] == 0 && vr[2] == -2);
        vr = babel::ALGO::range(0, 3);
        assert(vr.size() == 3 && vr[0] == 0 && vr[2] == 2);
        vr = babel::ALGO::range(0, -3);
        assert(vr.size() == 3 && vr[0] == 0 && vr[2] == -2);
        vr = babel::ALGO::range(6, -3);
        assert(vr[0] == 6 && vr[vr.size()-1]==-2);
        vr = babel::ALGO::range(6, -3, 0);
        assert(vr.size() == 1 && vr[0] == 6);
        vr = babel::ALGO::range(6, -3, 2);
        assert(vr.empty());
        auto zeros = babel::ALGO::zeros(3, 2);
        assert(zeros.size() == 3 && zeros[0].size() == 2 && zeros[0][0] == 0);
        auto zeros1 = babel::ALGO::zeros(4);
        assert(zeros1.size() == 4 && zeros1[3] == 0);
        auto ones = babel::ALGO::ones(3, 2);
        assert(ones.size() == 3 && ones[0].size() == 2 && ones[0][0] == 1);
        auto ones1 = babel::ALGO::ones(4);
        assert(ones1.size() == 4 && ones1[3] == 1);
        float f = 3.14f;
        auto astype = babel::ALGO::asType<int>(f);
        assert(astype==3);
        astype = 213;
        auto astypestr = babel::ALGO::asType<std::string>(astype);
        assert(astypestr == "213");
        auto astypeint = babel::ALGO::asType<int32_t>(astypestr);
        assert(astypeint == 213);
        {
            struct P
            {
                int x = 2;

                virtual void del() = 0;
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
            auto z = babel::ALGO::asType<P *>(y);
            auto z1 = babel::ALGO::asType<P *>(&y);
            assert(z->x == 4 && z1->x == 4);
            auto z2 = babel::ALGO::asType<Y *>(z);
            auto z3 = babel::ALGO::asType<Y *>(z1);
            assert(z2->x == 4 && z3->x == 4);
            assert(z2->z == 12 && z3->z == 12);
            auto z4 = babel::ALGO::asType<P *>(z2);
            auto z5 = babel::ALGO::asType<P *>(z3);
            assert(z4->x == 4 && z5->x == 4);

            std::vector<int> vtype = {3, 1 , 2};
            std::list <float> ltype;
            ltype = babel::ALGO::asType<decltype(ltype)>(vtype);


            std::list <float> ltype1 = {1.f, 2.f, 3.f};
            std::vector<int> vtype1;
            vtype1 = babel::ALGO::asType<decltype(vtype1)>(ltype1);

            assert(vtype1[0] == 1 && vtype1[1] == 2 && vtype1[2] == 3);
            auto bltype = ltype.begin();
            assert(*bltype == 3);
            ++bltype;
            assert(*bltype == 1);
            ++bltype;
            assert(*bltype == 2);

            std::vector<std::string> ts = {"3", "1" , "5"};
            std::vector<int> ti;
            ti = babel::ALGO::asType<decltype(ti)>(ts);


            std::vector<int> ti1 = {1, 2, 3};
            std::vector<std::string> ts1;
            ts1 = babel::ALGO::asType<decltype(ts1)>(ti1);

            assert(ti[0] == 3 && ti[1] == 1 && ti[2] == 5);
            assert(ts[0] == "3" && ts[1] == "1" && ts[2] == "5");
            assert(ts1[0] == "1" && ts1[1] == "2" && ts1[2] == "3");
            assert(ti1[0] == 1 && ti1[1] == 2 && ti1[2] == 3);

            auto lambda = [](int pt) -> std::unique_ptr<std::string> {
                return std::make_unique<std::string>(std::to_string(pt*pt));};
            int xlamb = 2;
            auto ylamb = babel::ALGO::asType<std::unique_ptr<std::string>>(xlamb, lambda);
            assert(xlamb == 2 && *ylamb == std::to_string(xlamb*xlamb));
            auto PXP = babel::ALGO::asType<int>(std::string("25"), [](const std::string&)->int{return 555;});
            assert(PXP == 555);
            PXP = babel::ALGO::asType<int>(std::string("25"));
            assert(PXP == 25);
            auto l1 = [](const std::vector<std::string>& vec) -> std::vector<int>
            {
                int suma = 0;
                for(const auto& El : vec)
                {
                    suma += babel::ALGO::string_to<int>(El);
                }
                return {suma};
            };
            auto l2 = [](const std::string& Str) -> int
            {
                return babel::ALGO::string_to<int>(Str) * 10;
            };
            std::vector<std::string> pps ={"1", "2"};
            std::vector<int> vv, vv1;
            vv = babel::ALGO::asType<decltype(vv)>(pps, l1);
            assert(vv.size() == 1 && vv[0] == 3);

            vv1 = babel::ALGO::asType<decltype(vv1)>(pps, l2);
            assert(vv1.size() == 2 && vv1[0] == 10 && vv1[1] == 20);

            std::string st1 = "test";
            auto st2 = babel::ALGO::asType<std::string>(std::move(st1));
            assert(st1.empty() && st2 == "test");
            st1 = babel::ALGO::asType<std::string>(st2);
            assert(st1== "test" && st2 == "test");
        }
    }

#ifdef _WIN32
    void WINDOWSCONV_HPP() //DONE
    {
        std::string str = "testowy napis";
        auto lpc = babel::WINDOWS::CONVERSION::str_to_lpcwstr(str);
        auto p = lpc.get_LPCWSTR();
        assert(p != nullptr);
        auto &ws = lpc.get_wstring();
        assert(!ws.empty());
    }
#endif

    void REQUEST_HPP() //DONE
    {
        babel::REQ::request req;
        assert(!req.has_request() && req.is_empty() && req.request_size() == 0);
        req.clear();
        int p = 0;
        req.send_req([]() { return 33; }, &p);
        req.send_req([]() { return 37; }, &p);
        assert(req.has_request() && !req.is_empty() && req.request_size() == 2);
        req.pop();
        assert(req.has_request() && !req.is_empty() && req.request_size() == 1);
        req.call();
        assert(!req.has_request() && req.is_empty() && req.request_size() == 0);
        assert(p == 37);
        req.call_all();
        req.pop_n_if_possible(100);
        std::unique_ptr<int> pq;
        req.send_req([]() { return std::make_unique<int>(13); }, &pq);
        req.call_if_possible();
        assert(*pq == 13);
        req.send_req([](const std::unique_ptr<int> &uq) { return std::make_unique<int>(( *uq ) * 2); }, &pq, pq);
        req.call_n(1);
        assert(*pq == 26);
    }

    void TEXT_HPP()
    {
        babel::TEXT::text tekst("Wojtek krolo zloty");
        tekst.set_text("testowy Tekst to");
        assert(tekst.count('t') == 4 && tekst.count('T') == 1 && tekst.count('p') == 0);
        assert(tekst.find("Tekstt") == nullptr);
        assert(tekst.find("owy") != nullptr);
        assert(tekst.find("t to") != nullptr);
    }

    void START_ALL_TEST(const int times = 1)
    {
        auto start_test = []() {
            TEXT_HPP();
            WRAPER_HPP();
            VARIADIC_HPP();
            TIME_HPP();
            OPTIONAL_HPP();
            MUST_HAVE_HPP();
            MATH_HPP();
            FILE_SYSTEM_HPP();
            CHAR_HPP();
            ANY_HPP_VOID_ANY();
            ANY_HPP_POLY_ANY();
            ALGORITHM_HPP();
#ifdef _WIN32
            WINDOWSCONV_HPP();
#endif
            REQUEST_HPP();
        };
        if ( times <= 0 )
        {
            while ( 1 ) // NOLINT
                start_test();
        } else
        {
            for ( int i = 0 ; i < times ; ++i )
                start_test();
        }

    }
}

#endif //CLIONPROJECT_TESTER_HPP
