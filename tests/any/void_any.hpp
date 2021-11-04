#ifndef TESTS_ANY_VOID_HPP
#define TESTS_ANY_VOID_HPP

#include "babel.hpp"
#include <cassert>

namespace TESTING{
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
}

#endif  // TESTS_ANY_VOID_HPP
