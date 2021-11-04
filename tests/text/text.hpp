#ifndef TESTS_TEXT_HPP
#define TESTS_TEXT_HPP

#include "babel.hpp"

namespace TESTING{
    void TEXT_HPP()
    {
        babel::TEXT::text tekst("Wojtek krolu zloty");
        tekst.set_text("testowy Tekst to krolewicz");
        babel::TEXT::text tekst2("testowy Tekst to");
        assert(tekst.count('t') == 4 && tekst.count('T') == 1 && tekst.count('p') == 0);
        assert(tekst.find("Tekstt") == nullptr);
        assert(tekst.find("owy") != nullptr);
        assert(tekst2.find("t to") != nullptr);
        assert(tekst.find("krolewiczc") == nullptr);
        assert(tekst.find("krolewiczczczczcz") == nullptr);
    }
}

#endif  //  TESTS_TEXT_HPP
