#ifndef TESTS_CHAR_HPP
#define TESTS_CHAR_HPP

#include "babel.hpp"
#include <cassert>

namespace TESTING{
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
}

#endif  // TESTS_CHAR_HPP
