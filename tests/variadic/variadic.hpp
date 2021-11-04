#ifndef TESTS_VARIADIC_HPP
#define TESTS_VARIADIC_HPP

#include "babel.hpp"

namespace TESTING{
    void VARIADIC_HPP() // DONE
    {

        babel::VARIADIC::holder<int, int, int, int, int> p(3, 4, 12, 5, 14);
        assert(p.get<0>() == 3 && p.get<3>() == 5);
        babel::VARIADIC::holder<int, int, int, int, int> p1(p);
        p1.get<4>() = 200;
        assert(p1.get<0>() == 3 && p1.get<3>() == 5 && p1.get<4>() == 200 && p.get<4>() == 14);
        babel::VARIADIC::holder<int> p3(15);
        assert(p3.get<0>() == 15);
        babel::VARIADIC::holder<int, std::string, float, double> dd(3, std::string("TestString"), 12.f, 5.25);
        assert(dd.get<0>() == 3);
        assert(dd.get<1>() == "TestString");
        assert(dd.get<2>() >= 11.99f && dd.get<2>() <= 12.1f);
        assert(dd.get<3>() >= 5.249 && dd.get<3>() <= 5.2501);

    }
}

#endif  // TESTS_VARIADIC_HPP
