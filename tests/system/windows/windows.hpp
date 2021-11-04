#ifndef TESTS_WINDOWS_HPP
#define TESTS_WINDOWS_HPP

#include "babel.hpp"

namespace TESTING{

#ifdef _WIN32

    void WINDOWSCONV_HPP() //DONE
    {
        std::string str = "testowy napis";
        auto lpc = babel::WINDOWS::CONVERSION::str_to_lpcwstr(str);
        auto p = lpc.get_LPCWSTR();
        assert(p != nullptr);
        auto &ws = lpc.get_wstring();
        assert(!ws.empty());
    }

#endif
}

#endif