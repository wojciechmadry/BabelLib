#ifndef TESTS_TIME_HPP
#define TESTS_TIME_HPP

#include "babel.hpp"

namespace TESTING{
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
}

#endif  // TESTS_TIME_HPP
