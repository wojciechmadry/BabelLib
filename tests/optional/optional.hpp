#ifndef TESTS_OPTIONAL_HPP
#define TESTS_OPTIONAL_HPP

#include "babel.hpp"

namespace TESTING{
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
}

#endif  // TESTS_OPTIONAL_HPP
