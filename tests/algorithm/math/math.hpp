#ifndef TESTS_MATH_HPP
#define TESTS_MATH_HPP

#include "babel.hpp"

namespace TESTING{
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
}

#endif  // TESTS_MATH_HPP
