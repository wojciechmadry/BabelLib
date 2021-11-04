#ifndef TESTS_WRAPPER_HPP
#define TESTS_WRAPPER_HPP

#include "babel.hpp"
#include <cassert>

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
}

#endif  // TESTS_WRAPPER_HPP
