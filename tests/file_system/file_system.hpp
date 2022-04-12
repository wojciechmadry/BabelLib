#ifndef TESTS_FILE_SYSTEM_HPP
#define TESTS_FILE_SYSTEM_HPP

#include "babel.hpp"

namespace TESTING{
    void FILE_SYSTEM_HPP() //DONE
    {
        {
            std::ofstream f("FILE_SYSTEM_TEST.cpp", std::ios::out);
            f << "";
            f.close();
        }
        {
            std::ofstream f("FILE_SYSTEM_TEST.hpp", std::ios::out);
            f << "";
            f.close();
        }
        std::fstream f1("FILE_SYSTEM_TEST.cpp", std::ios::in | std::ios::binary);
        std::fstream f2("FILE_SYSTEM_TEST.hpp", std::ios::in | std::ios::binary);
        assert(f1.good());
        assert(f2.good());
        babel::FILE_SYS::close_file(f1, f2);
        assert(!f1.is_open() && !f2.is_open());

        assert(!babel::FILE_SYS::file_exist("dhshds"));
        assert(!babel::FILE_SYS::folder_exist("dhshds"));
        assert(!babel::FILE_SYS::file_folder_exist("dhshds"));
    }
}

#endif  // TESTS_FILE_SYSTEM_HPP
