#include <iostream>
#include "babel.hpp"
#include "tester.hpp"
int main()
{
    std::cout << "Compiler is 64bit ? : " << babel::COMPILER_IS_64B << '\n';
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';
    srand(static_cast<unsigned>(time(nullptr)));
    auto T = babel::TIME::measure_time(1, TESTING::START_ALL_TEST, 1);
    std::cout << "Done\nTime : " << T << " seconds\n";
    babel::ITERATOR::generator<std::string> gen("Das");
    std::vector<std::string> t;
    std::transform(gen.begin(10), gen.end(), std::back_inserter(t), [](const auto& g) {return g;});
    std::cout << t.size();
    return 0;
}
