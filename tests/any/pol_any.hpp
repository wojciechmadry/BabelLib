#ifndef TESTS_ANY_POL_HPP
#define TESTS_ANY_POL_HPP

#include "babel.hpp"
#include <cassert>

namespace TESTING{
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
}

#endif  // TESTS_ANY_POL_HPP
