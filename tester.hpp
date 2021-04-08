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
        assert(babel::MATH::max(0,13,2,5,2,20) == 20);

        assert(babel::MATH::min(15, 5) == 5 && babel::MATH::min(5, 15) == 5);
        assert(babel::MATH::min(0,13,2,5,2,20,-1) == -1);

        std::vector<int> cont = {3,5,2,-1,5,8};

        assert(babel::MATH::max(cont) == 8 && babel::MATH::min(cont) == -1);

        assert(!babel::MATH::is_neg(5) && babel::MATH::is_neg(-5));

        assert(babel::MATH::factorial(5) == babel::MATH::factorial<5>() && babel::MATH::factorial(5) == 120);

        double d = babel::MATH::binomial_coefficient<5, 3>();
        assert( babel::MATH::binomial_coefficient(5, 3) == d );

        assert(babel::MATH::fib(4) == 3);
        assert(babel::MATH::fib(6) == 8);
        assert(compare(babel::MATH::delta(2,4,3),-8));
        assert(babel::MATH::square_area(3) == 9);
        assert(babel::MATH::square_circumference(3) == 12);
        assert(babel::MATH::cube_volume(4) == 64);
        assert(babel::MATH::rectangle_area(3, 2) == 6);
        assert(babel::MATH::rectangle_circumference(3, 2) == 10);
        assert(babel::MATH::cuboid_volume(2,3,4) == 24);
        assert(compare(babel::MATH::circle_area<double>(3), 28.26));
        assert(compare(babel::MATH::circle_area<int>(3), 28));
        assert(compare(babel::MATH::circle_circumference<double>(3), 18.84 ));
        assert(compare(babel::MATH::circle_circumference<int>(3), 18 ));
        assert(compare(babel::MATH::sphere_volume<double>(4), 267.94, 0.5));
        assert(compare(babel::MATH::sphere_volume<int>(4), 268));
        assert(compare(babel::MATH::cylinder_volume<double>(3, 8), babel::MATH::circle_area<double>(3)*8.0 ) );
        assert(compare(babel::MATH::cone_volume<double>(3, 2), babel::MATH::cylinder_volume<double>(3,2) * 1.0/3.0 ));
        assert(compare(babel::MATH::kW_to_HP<double>(babel::MATH::HP_to_kW<double>(30)), babel::MATH::kW_to_HP<double>(babel::MATH::HP_to_kW<double>(30))));
        assert(babel::MATH::map<double>(305,5,905,0,1) >= 0.0 && babel::MATH::map<double>(305,5,905,0,1) <= 1.0);

    }

    void START_ALL_TEST(const int times = 1)
    {
        auto start_test = []() {
            WRAPER_HPP();
            VARIADIC_HPP();
            TIME_HPP();
            OPTIONAL_HPP();
            MUST_HAVE_HPP();
            MATH_HPP();
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
