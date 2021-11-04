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
        auto files = babel::FILE_SYS::scan_folder("../babLib");
        assert(!( babel::FILE_SYS::file_extension(files[0]) == "hpp" ));
        assert(babel::FILE_SYS::file_without_extension(files[0]).find("hpp") == std::string::npos);
        assert(!babel::FILE_SYS::filename_contain(files[0], "hpp"));
        //assert(babel::FILE_SYS::load_txt_to_vector("../loremipsum.txt").size() == 21600);
        //auto li = babel::FILE_SYS::load_txt("../loremipsum.txt");
        assert(babel::FILE_SYS::file_exist("../babel.hpp"));
        assert(!babel::FILE_SYS::file_exist("dhshds"));
        assert(!babel::FILE_SYS::file_exist("../cmake-build-release"));

        assert(!babel::FILE_SYS::folder_exist("../babel.hpp"));
        assert(!babel::FILE_SYS::folder_exist("dhshds"));
        assert(babel::FILE_SYS::folder_exist("../Screen"));

        assert(babel::FILE_SYS::file_folder_exist("../babel.hpp"));
        assert(!babel::FILE_SYS::file_folder_exist("dhshds"));
        assert(babel::FILE_SYS::file_folder_exist("../Screen"));
    }
}

#endif  // TESTS_FILE_SYSTEM_HPP
