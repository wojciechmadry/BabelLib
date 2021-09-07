//
// Created by Wojtek on 08.04.2021.
//

#ifndef CLIONPROJECT_TESTER_HPP
#define CLIONPROJECT_TESTER_HPP

#include "babel.hpp"
#include <cassert>
#include <list>

namespace TESTING{

    void WRAPER_HPP() //DONE
    {
        babel::WRAPER::wrap<int> p {0};
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
        p1 = 15;
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

        babel::VARIADIC::holder<int, int, int, int, int> p(3, 4, 12, 5, 14);
        assert(p.get<0>() == 3 && p.get<3>() == 5);
        babel::VARIADIC::holder<int, int, int, int, int> p1(p);
        p1.get<4>() = 200;
        assert(p1.get<0>() == 3 && p1.get<3>() == 5 && p1.get<4>() == 200 && p.get<4>()==14);
        babel::VARIADIC::holder<int> p3(15);
        assert(p3.get<0>() == 15);
        babel::VARIADIC::holder<int, std::string, float, double> dd(3, std::string("TestString"), 12.f, 5.25);
        assert(dd.get<0>() == 3);
        assert(dd.get<1>() == "TestString");
        assert(dd.get<2>() >= 11.99f && dd.get<2>() <= 12.1f);
        assert(dd.get<3>() >= 5.249 && dd.get<3>() <= 5.2501);

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
        (void) p1;
        (void) p2;
        (void) p3;
        (void) p4;
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
        using namespace babel::ALGO::MATH::DERIVATIVE;
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


        assert(babel::ALGO::MATH::CONSTANT::E<double> > 2.7 && babel::ALGO::MATH::CONSTANT::E<double> < 2.72);
        assert(babel::ALGO::MATH::CONSTANT::PI<double> > 3.140 && babel::ALGO::MATH::CONSTANT::PI<double> < 3.142);
        assert(babel::ALGO::MATH::CONSTANT::sqrt_2<double> > 1.40 &&
               babel::ALGO::MATH::CONSTANT::sqrt_2<double> < 1.42);
        assert(babel::ALGO::MATH::CONSTANT::sqrt_3<double> > 1.731 &&
               babel::ALGO::MATH::CONSTANT::sqrt_3<double> < 1.733);
        assert(babel::ALGO::MATH::CONSTANT::PLANCK<double> > 6.62607004e-35 &&
               babel::ALGO::MATH::CONSTANT::PLANCK<double> < 6.62607004e-33);
        assert(babel::ALGO::MATH::CONSTANT::golden_ratio<double> > 1.617 &&
               babel::ALGO::MATH::CONSTANT::golden_ratio<double> < 1.619);


        assert(babel::ALGO::MATH::abs(-5) == 5 && babel::ALGO::MATH::abs(5) == 5);

        assert(babel::ALGO::MATH::max(15, 5) == 15 && babel::ALGO::MATH::max(5, 15) == 15);

        assert(babel::ALGO::MATH::min(15, 5) == 5 && babel::ALGO::MATH::min(5, 15) == 5);

        std::vector<int> cont = {3, 5, 2, -1, 5, 8};

        assert(babel::ALGO::MATH::max(cont) == 8 && babel::ALGO::MATH::min(cont) == -1);

        assert(!babel::ALGO::MATH::is_neg(5) && babel::ALGO::MATH::is_neg(-5));

        assert(babel::ALGO::MATH::factorial(5) == babel::ALGO::MATH::factorial<5>() &&
               babel::ALGO::MATH::factorial(5) == 120);

        double d = babel::ALGO::MATH::binomial_coefficient<5, 3>();
        assert(babel::ALGO::MATH::binomial_coefficient(5, 3) == d);

        assert(babel::ALGO::MATH::fib(4) == 3);
        assert(babel::ALGO::MATH::fib(6) == 8);
        assert(compare(babel::ALGO::MATH::delta(2, 4, 3), -8));
        assert(babel::ALGO::MATH::square_area(3) == 9);
        assert(babel::ALGO::MATH::square_circumference(3) == 12);
        assert(babel::ALGO::MATH::cube_volume(4) == 64);
        assert(babel::ALGO::MATH::rectangle_area(3, 2) == 6);
        assert(babel::ALGO::MATH::rectangle_circumference(3, 2) == 10);
        assert(babel::ALGO::MATH::cuboid_volume(2, 3, 4) == 24);
        assert(compare(babel::ALGO::MATH::circle_area<double>(3), 28.26));
        assert(compare(babel::ALGO::MATH::circle_area<int>(3), 27));
        assert(compare(babel::ALGO::MATH::circle_circumference<double>(3), 18.84));
        assert(compare(babel::ALGO::MATH::circle_circumference<int>(3), 18));
        assert(compare(babel::ALGO::MATH::sphere_volume<double>(4), 267.94, 0.5));
        assert(compare(babel::ALGO::MATH::sphere_volume<int>(4), 256));
        assert(compare(babel::ALGO::MATH::cylinder_volume<double>(3, 8),
                       babel::ALGO::MATH::circle_area<double>(3) * 8.0));
        assert(compare(babel::ALGO::MATH::cone_volume<double>(3, 2),
                       babel::ALGO::MATH::cylinder_volume<double>(3, 2) * 1.0 / 3.0));
        assert(compare(babel::ALGO::MATH::kW_to_HP<double>(babel::ALGO::MATH::HP_to_kW<double>(30)),
                       babel::ALGO::MATH::kW_to_HP<double>(babel::ALGO::MATH::HP_to_kW<double>(30))));
        assert(babel::ALGO::MATH::map<double>(305, 5, 905, 0, 1) >= 0.0 &&
               babel::ALGO::MATH::map<double>(305, 5, 905, 0, 1) <= 1.0);

        auto r = babel::ALGO::MATH::prime_factors(64u);
        assert(r.size() == 6);
        for ( auto num : r )
            assert(num == 2);
        r = babel::ALGO::MATH::prime_factors(210u);
        assert(r.size() == 4);
        assert(r[0] == 2 && r[1] == 3 && r[2] == 5 && r[3] == 7);
        r = babel::ALGO::MATH::prime_factors(1155u);
        assert(r.size() == 4);
        assert(r[0] == 3 && r[1] == 5 && r[2] == 7 && r[3] == 11);
        assert(babel::ALGO::MATH::gcd(24, 36) == 12);
        assert(babel::ALGO::MATH::lcm(24, 36) == 72);

        assert(babel::ALGO::MATH::gcd(256, 24) == 8);
        assert(babel::ALGO::MATH::lcm(256, 24) == 768);

        auto fx = babel::ALGO::MATH::find_x(-1.0, -11.0, 12.0);
        assert(fx.size() == 2 && fx[0] == -12 && fx[1] == 1);
        fx = babel::ALGO::MATH::find_x(2.0, -4.0, 2.0);
        assert(fx.size() == 1 && fx[0] == 1);
        fx = babel::ALGO::MATH::find_x(2.0, 6.0, 12.0);
        assert(fx.empty());


    }

    void FILE_SYSTEM_HPP() //DONE
    {
        {
            std::ofstream f("FILE_SYSTEM_TEST.cpp", std::ios::out);
            f << "";
            f.close();
        }
        {
            std::ofstream f("FILE_SYSTEM_TEST.hpp", std::ios::out);
            f << "";
            f.close();
        }
        std::fstream f1("FILE_SYSTEM_TEST.cpp", std::ios::in | std::ios::binary);
        std::fstream f2("FILE_SYSTEM_TEST.hpp", std::ios::in | std::ios::binary);
        assert(f1.good());
        assert(f2.good());
        babel::FILE_SYS::close_file(f1, f2);
        assert(!f1.is_open() && !f2.is_open());
        auto files = babel::FILE_SYS::scan_folder("../babLib");
        assert(!( babel::FILE_SYS::file_extension(files[0]) == "hpp" ));
        assert(babel::FILE_SYS::file_without_extension(files[0]).find("hpp") == std::string::npos);
        assert(!babel::FILE_SYS::filename_contain(files[0], "hpp"));
        //assert(babel::FILE_SYS::load_txt_to_vector("../loremipsum.txt").size() == 21600);
        //auto li = babel::FILE_SYS::load_txt("../loremipsum.txt");
        assert(babel::FILE_SYS::file_exist("../babel.hpp"));
        assert(!babel::FILE_SYS::file_exist("dhshds"));
        assert(!babel::FILE_SYS::file_exist("../cmake-build-release"));

        assert(!babel::FILE_SYS::folder_exist("../babel.hpp"));
        assert(!babel::FILE_SYS::folder_exist("dhshds"));
        assert(babel::FILE_SYS::folder_exist("../Screen"));

        assert(babel::FILE_SYS::file_folder_exist("../babel.hpp"));
        assert(!babel::FILE_SYS::file_folder_exist("dhshds"));
        assert(babel::FILE_SYS::file_folder_exist("../Screen"));
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
        d1.destroy_any<int>();
        d2.destroy_any<std::unique_ptr<int>>();
        d3.destroy_any<std::unique_ptr<int>>();
        d4 = std::string("pies");
        babel::ANY::destroy_any<std::string>(d4);
        assert(!d4.has_value() && !d2.has_value());
        std::string t = "pies";
        auto d5 = babel::ANY::VoidAny::make_any(std::move(t));
        assert(d5.cast<std::string>() == "pies" && t == ""); //NOLINT
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
        assert(d4.cast<std::string>() == "pies" && test == ""); //NOLINT
        d4.emplace<std::string>("testowy napis");
        assert(d4.cast<std::string>() == "testowy napis");
        d3.emplace<std::string>("t2");
        assert(d4 == d3 && !d4.cmp<std::string>(d3));
        d3.reset();
        assert(d4 != d3 && !d4.cmp<std::string>(d3));
    }

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
        tekst.set_text("testowy Tekst to krolewicz");
        babel::TEXT::text tekst2("testowy Tekst to");
        assert(tekst.count('t') == 4 && tekst.count('T') == 1 && tekst.count('p') == 0);
        assert(tekst.find("Tekstt") == nullptr);
        assert(tekst.find("owy") != nullptr);
        assert(tekst2.find("t to") != nullptr);
        assert(tekst.find("krolewiczc") == nullptr);
        assert(tekst.find("krolewiczczczczcz") == nullptr);
    }

    void CONCEPT_HPP()
    {
        assert(!babel::CONCEPTS::IS_ANY_POINTER<int>);
        assert(babel::CONCEPTS::IS_ANY_POINTER<int *>);
        assert(babel::CONCEPTS::IS_ANY_POINTER<std::unique_ptr<int>>);
        assert(babel::CONCEPTS::IS_ANY_POINTER<std::shared_ptr<int>>);
        assert(babel::CONCEPTS::IS_ANY_POINTER<std::weak_ptr<int>>);
        assert(!babel::CONCEPTS::IS_ANY_POINTER<std::vector<int>>);
        assert(!babel::CONCEPTS::IS_ANY_POINTER<std::vector<int *>>);
        assert(!babel::CONCEPTS::IS_ANY_POINTER<std::string>);
        assert(!babel::CONCEPTS::IS_ANY_POINTER<std::reference_wrapper<int>>);
        assert(babel::CONCEPTS::IS_ANY_POINTER<std::reference_wrapper<int *>>);
    }

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

    void LIST_HPP()
    {
        using namespace babel::CONTAINER;
        list<int> l;
        assert(l.size() == 0);
        l.push_back(5);
        assert(l.size() == 1 && l[0] == 5);
        l.push_back(10);
        assert(l.size() == 2 && l[0] == 5 && l[1] == 10);
        l.push_back(20);
        assert(l.size() == 3 && l[0] == 5 && l[1] == 10 && l[2] == 20);
        l.clear();
        assert(l.size() == 0);
        l.push_front(10);
        assert(l.size() == 1 && l[0] == 10);
        l.push_front(12);
        assert(l.size() == 2 && l[0] == 12 && l[1] == 10);
        l.push_front(13);
        assert(l.size() == 3 && l[0] == 13 && l[1] == 12 && l[2] == 10);
        l.clear();
        assert(l.size() == 0);
        list<int> _l(15, 5);
        assert(_l[0] == 5 && _l[14] == 5 && _l.size() == 15);
        l = list<int>({1, 2, 3, 4, 5});
        assert(l.size() == 5 && l[0] == 1 && l[4] == 5);
        l.pop_back();
        assert(l[3] == 4);
        l.pop_back();
        assert(l[2] == 3);
        l.pop_back();
        assert(l[1] == 2);
        l.pop_back();
        assert(l[0] == 1);
        l.pop_back();
        assert(l.size() == 0);
        l = list<int>({1, 2, 3, 4, 5});
        l.pop_front();
        assert(l[0] == 2);
        l.pop_front();
        assert(l[0] == 3);
        l.pop_front();
        assert(l[0] == 4);
        l.pop_front();
        assert(l[0] == 5);
        l.pop_front();
        assert(l.size() == 0);
        l = list<int>({1, 2, 3, 4, 5});
        assert(*l.find(5) == 5);
        assert(*l.find(2) == 2);
        assert(l.find(312) == nullptr);
        assert(*l.find([](int my_i) { return my_i > 3; }) == 4);
        assert(l.find([](int my_i) { return my_i > 30; }) == nullptr);
        l[0] = 12;
        assert(l[0] == 12);
        _l = l;
        assert(_l[0] == 12 && _l[4] == 5 && _l.size() == 5);
        l = list<int>({1, 2, 3});
        l.remove(2);
        assert(l.size() == 2 && l[0] == 1 && l[1] == 3);
        _l = l;
        l.remove(1);
        _l.remove(3);
        assert(l.size() == 1 && _l.size() == 1);
        assert(l[0] == 3 && _l[0] == 1);
        l.remove(3);
        _l.remove(1);
        assert(l.size() == 0 && _l.size() == 0);
        l.push_back(2);
        l.push_front(4);
        l.push_back(3);
        assert(l.size() == 3 && l[0] == 4 && l[1] == 2 && l[2] == 3);
        l.remove([](int y) { return y == 3; });
        assert(l.size() == 2 && l[0] == 4 && l[1] == 2);
        l.remove([](int y) { return y == 3; });
        assert(l.size() == 2);
        l.clear();
        l = {1, 2, 3};
        assert(l.size() == 3 && l[0] == 1 && l[1] == 2 && l[2] == 3);
        l.clear();
        for ( int i = 10 ; i >= 0 ; --i )
            l.push_in_order(i, std::greater<>());
        for ( int i = 0 ; i < 10 ; ++i )
            assert(l[static_cast<std::size_t>(i)] == i);
        l.clear();
        for ( std::size_t i = 0 ; i < 10 ; ++i )
        {
            l.push_in_order(static_cast<int>(i), std::greater<>());
            assert(l[i] == static_cast<int>(i));
        }
        l.clear();
        for ( int i = 0 ; i < 10 ; ++i )
            l.push_in_order(i, std::less<>());
        for ( int i = 9 ; i >= 0 ; --i )
            assert(l[static_cast<std::size_t>(9 - i)] == i);
        l.clear();
        babel::ALGO::MATH::random_generator rg;
        for ( std::size_t i = 0 ; i < 10000 ; ++i )
            l.push_in_order(rg.generate(0, 100000), std::greater<>());
        for ( std::size_t i = 0 ; i < 10000 - 1 ; ++i )
            assert(l[i + 1] >= l[i]);
        l.clear();
        for ( int i = 0 ; i < 100000 ; ++i )
            l.push_back(i);
        l.clear();
        l.push_back({3, 1, 2});
        assert(l.size() == 3 && l[0] == 3 && l[1] == 1 && l[2] == 2);
        l.clear();
        l.push_back({1, 1, 1, 1, 1, 1, 1, 1, 1});
        for ( auto el : l )
            assert(el == 1);
        l.clear();
        l.push_back(1);
        assert(l.size() == 1 && l[0] == 1);
        l.remove(1);
        assert(l.size() == 0);
        l.push_front(1);
        assert(l.size() == 1 && l[0] == 1);
        l.remove(1);
        assert(l.size() == 0);
        l.push_front(5);
        l.push_back(2);
        assert(l.size() == 2 && l[1] == 2 && l[0] == 5);
        l.remove(2);
        assert(l.size() == 1 && l[0] == 5);
        l.remove(5);
        assert(l.size() == 0);
        l.push_front(5);
        l.push_back(2);
        l.remove(5);
        assert(l.size() == 1 && l[0] == 2);
        l.remove(2);
        assert(l.size() == 0);
    }

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

    void WRITER_READER_ITERATOR()
    {
        std::string s;
        std::ofstream of("test.txt");
        babel::ITERATOR::writer W(of);
        W.write("Linia1\n");
        W.write("Linia2");
        W.writeln("Linia3");
        W.writeln("Linia4");
        W.writeln(15);
        W.close();
        std::ofstream of1("vector.txt");
        W = of1;
        std::vector<double> DOUBLE = {3.14, 3.22, 0.15, 25.4};
        std::transform(DOUBLE.begin(), DOUBLE.end(), W.back_inserter(false),
                       [](auto D) { return D; });
        W.close();
        std::ofstream of2("vectornl.txt");
        W = of2;
        std::transform(DOUBLE.begin(), DOUBLE.end(), W.back_inserter(true),
                       [](auto D) { return D; });
        W.close();


        std::ifstream f {"test.txt"};
        std::ifstream f1 {"vector.txt"};
        std::ifstream f3 {"vectornl.txt"};

        babel::ITERATOR::reader rd(f);
        babel::ITERATOR::reader rd1(f1);
        babel::ITERATOR::reader rd2(f3);

        std::vector<std::string> lines = {"Linia1", "Linia2Linia3", "Linia4", "15"};
        auto beg = lines.begin();
        while ( rd )
        {
            assert(( *beg ) == rd.line());
            ++beg;
        }
        std::string line_f1 = "3.143.220.1525.4";
        for ( const auto &Line : rd1 )
        {
            assert(Line == line_f1);
        }
        rd2.read();
        lines = {"3.22", "0.15", "25.4"};
        beg = lines.begin();
        for ( const auto &Line : rd2 )
        {
            assert(Line == ( *beg ));
            ++beg;
        }
    }

    void SHA_HASH_TEST() noexcept
    {
        std::vector<std::string> SHA1 = {
                "2aae6c35c94fcfb415dbe95f408b9ce91ee846ed",
                "667922d670dedc11b42f2559ab450464b7acb991",
                "efc0268c45856d09a2c8c555c0a9ba3aba414f73",
                "b965981445b816ec8430ad837fe4fb94a6676072",
                "8efd86fb78a56a5145ed7739dcb00c78581c5375",
                "da39a3ee5e6b4b0d3255bfef95601890afd80709",
                "1e5ae15c99b98ab45c89d87a159f361e974ac21e"
        };
        std::vector<std::string> SHA224 = {
                "2f05477fc24bb4faefd86517156dafdecec45b8ad3cf2522a563582b",
                "f84e9b896d9b90467727704a7d274dd5d2b58a8f450c25412e6e2815",
                "b00dc19d9ac2f00af60a68605d5a2bcb3518d103c75b7ba54bee914a",
                "c6627c8efd18bcac1da46f2fe29ada915628381a30ca33ae3ef8fef5",
                "8a27683839f9c2be2028e11d0e622fb152309c1c29392d44669c4154",
                "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f",
                "556f3db59bdb9ebb843967879c5ab41109e0863a0a4fce1ef2d40b06"
        };
        std::vector<std::string> SHA256 = {
                "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9",
                "5a1da66f7a404f517a39e474fab04a9cf38df2167f826e673ce759a760ad9501",
                "e16ae14d7186dd2565a8bf048818039cca6a003d501a83a2dbe2d90d0be147e3",
                "c19b220990b2f6e22b005446fc9c78c086041d06b75cbe476302d5f6cc9f06e3",
                "e3b98a4da31a127d4bde6e43033f66ba274cab0eb7eb1c70ec41402bf6273dd8",
                "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
                "8304f43e17bef742c28347684d6b713d404ea0251a5960ce9b520b774b4ac015"
        };
        std::vector<std::string> SHA384 = {
                "fdbd8e75a67f29f701a4e040385e2e23986303ea10239211af907fcbb83578b3e417cb71ce646efd0819dd8c088de1bd",
                "5472b6207632e03b124e2e2070db5c173b1c2d2187b39ac97fe20428297bfcf4f1c610fa6e0fce32789ef408bd22da61",
                "3ab37014cf9dbc295be4a1cd04e65e379fb52942c649ae81940cdbb389b3f8a689244a62d93b40d47832f52e15b52adf",
                "02fe725cc73b204b83a4b35b3281cd1d0a6e9a96c73f4d46e822fd990324ea61c358b595645b557bf39b960b4990fca4",
                "e7cdceeaff40fcf3eb07011b4facb47e6c06f82d243289ca9e598282f1e58ea4ee2378d5772c26e926ecbffba13f6d53",
                "38b060a751ac96384cd9327eb1b1e36a21fdb71114be07434c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b",
                "7ffa20f03b8e110e6f0578c72cb697b282147eeaba17ffc8900ccc145115aa1c89994cc8206aabaca0b5ad480958b0c8"
        };
        std::vector<std::string> SHA512 = {
                "309ecc489c12d6eb4cc40f50c902f2b4d0ed77ee511a7c7a9bcd3ca86d4cd86f989dd35bc5ff499670da34255b45b0cfd830e81f605dcf7dc5542e93ae9cd76f",
                "c293bba14663b092d34a2a8610a4cdc1e11a6483bb55c6255ac5357a5c849e1b58ce3c0906100c641a6f184f9b1d45ab88a44be15e59239ccf2331425e493a66",
                "5a04eca1ef9b7a92843017ee49b421fc1381eb0ae2d3e72e73731c99fc0cc139b984551d12ea64374855e63f79cfb2d8e25e834441ba87179fcf8addbfc79933",
                "e38bd66bb3368458296ac3c9ecc5d634da032ca1f38926f193c7e66324ca3a45bc283916d3727b32581dc9b9e9a1fbc1e857eafb612b1d0ad713de09caa38211",
                "99f97d455d5d62b24f3a942a1abc3fa8863fc0ce2037f52f09bd785b22b800d4f2e7b2b614cb600ffc2a4fe24679845b24886d69bb776fcfa46e54d188889c6f",
                "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e",
                "24c140f70848fc37a5a9d96ec649bc0da524d0a96e5a915903745cb462b02cfd0be9f77050bc4450b9e0dd92a081c750fa5ed1b6584247594096bc2787ce76ba"
        };

        std::vector<std::string> SHA512_224 = {
                "22e0d52336f64a998085078b05a6e37b26f8120f43bf4db4c43a64ee",
                "0f4b7f5c8b81a5338ab38cdd23fe88e9ea9722b7216ea3e093f838e7",
                "aea4eaf76b3c88d8fc7523de2fb1cb0697c236e6a886dd66d163858f",
                "57dbe76c65925a7ef7c8ef1d00f3b88b39aa214ede7254e0e1d82143",
                "4577aa10739fb44cbabf18b46117804ddeac21c40b9462844f071523",
                "6ed0dd02806fa89e25de060c19d3ac86cabb87d6a0ddd05c333b84f4",
                "dbb893f21b6c41b6180356b6e37b66a9bbd218d3849b5ac65880fa58"
        };

        std::vector<std::string> SHA512_256 = {
                "0ac561fac838104e3f2e4ad107b4bee3e938bf15f2b15f009ccccd61a913f017",
                "c0ed197119e31ab545a395c1bd2eb01207a78cbc885ca0b603b8be66f8e952cc",
                "0df7265e8b48c6b436d887dc4b9990c183e674ee8ccdb13080149da87a27aa0a",
                "33ad829b2c7c2c8489a07294bf7c4c0747bfc81e20f9b8994e1b2d2f069e6bb1",
                "91c9cb62865a010e804e1ebc896a753939decc6a0baaf00951e79aa9f2ad8c87",
                "c672b8d1ef56ed28ab87c3622c5114069bdd3ad7b8f9737498d0c01ecef0967a",
                "b3c056a85d2b20832c77c0dae15016d972f2b8eca74aa23332456656c38248a9"
        };

        std::vector<std::string> msg = {
                "hello world",
                "hello world,hello world,hello world",
                "hello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello worldhello world",
                "asgasmngmxczmvmxz mcxz kasf asf as",
                "t",
                "",
                "TESTED STRING"
        };
        for ( std::size_t i = 0 ; i < msg.size() ; ++i )
        {
            assert (babel::ALGO::CRYPT::sha1(msg[i]) == SHA1[i]);
            assert (babel::ALGO::CRYPT::sha224(msg[i]) == SHA224[i]);
            assert (babel::ALGO::CRYPT::sha256(msg[i]) == SHA256[i]);
            assert (babel::ALGO::CRYPT::sha384(msg[i]) == SHA384[i]);
            assert (babel::ALGO::CRYPT::sha512(msg[i]) == SHA512[i]);
            assert (babel::ALGO::CRYPT::sha512t<224>(msg[i]) == SHA512_224[i]);
            assert (babel::ALGO::CRYPT::sha512t<256>(msg[i]) == SHA512_256[i]);
        }
    }

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

    void START_ALL_TEST(const int times = 1)
    {
        auto start_test = []() {
            SHA_HASH_TEST();
            RANGES_ITERATOR();
            ENUMERATE_ITERATOR();
            LIST_HPP();
            DYNAMIC_ARRAY_HPP();
            CONCEPT_HPP();
            TEXT_HPP();
            WRAPER_HPP();
            VARIADIC_HPP();
            TIME_HPP();
            OPTIONAL_HPP();
            MATH_HPP();
            if ( babel::COMPILER_IS_64B ) //NOLINT //TODO on 32 bit clang compiler, cant see files
            {
                FILE_SYSTEM_HPP();
                WRITER_READER_ITERATOR();
            }
            CHAR_HPP();
            ALGORITHM_HPP();
            TOKENS_HPP();

#ifdef _WIN32
            WINDOWSCONV_HPP();
#endif
            REQUEST_HPP();

            ANY_HPP_VOID_ANY();
            ANY_HPP_POLY_ANY();
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
