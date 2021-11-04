#ifndef TESTS_WRITE_AND_READ_HPP
#define TESTS_WRITE_AND_READ_HPP

#include "babel.hpp"

namespace TESTING{
    void WRITER_READER_ITERATOR()
    {
        std::string s;
        std::ofstream of("test.txt");
        babel::ITERATOR::writer W(of);
        W.write("Linia1\n");
        W.write("Linia2");
        W.writeln("Linia3");
        W.writeln("Linia4");
        W.writeln(15);
        W.close();
        std::ofstream of1("vector.txt");
        W = of1;
        std::vector<double> DOUBLE = {3.14, 3.22, 0.15, 25.4};
        std::transform(DOUBLE.begin(), DOUBLE.end(), W.back_inserter(false),
                       [](auto D) { return D; });
        W.close();
        std::ofstream of2("vectornl.txt");
        W = of2;
        std::transform(DOUBLE.begin(), DOUBLE.end(), W.back_inserter(true),
                       [](auto D) { return D; });
        W.close();


        std::ifstream f {"test.txt"};
        std::ifstream f1 {"vector.txt"};
        std::ifstream f3 {"vectornl.txt"};

        babel::ITERATOR::reader rd(f);
        babel::ITERATOR::reader rd1(f1);
        babel::ITERATOR::reader rd2(f3);

        std::vector<std::string> lines = {"Linia1", "Linia2Linia3", "Linia4", "15"};
        auto beg = lines.begin();
        while ( rd )
        {
            assert(( *beg ) == rd.line());
            ++beg;
        }
        std::string line_f1 = "3.143.220.1525.4";
        for ( const auto &Line : rd1 )
        {
            assert(Line == line_f1);
        }
        rd2.read();
        lines = {"3.22", "0.15", "25.4"};
        beg = lines.begin();
        for ( const auto &Line : rd2 )
        {
            assert(Line == ( *beg ));
            ++beg;
        }
    }

}

#endif  // TESTS_WRITE_AND_READ_HPP
