#include <iostream>
#include "babel.hpp"
#include "tester.hpp"
#include <cassert>





int main()
{


    std::cout << "Compiler is 64bit ? : " << babel::COMPILER_IS_64B << '\n';
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';
    auto T = babel::TIME::measure_time(1, TESTING::START_ALL_TEST, 1);
    std::cout << "Done\nTime : " << T << " seconds\n";

    float test_f = 3.14f;
    babel::CONTAINER::RingBuffer<float, 20> rb;
    //  auto p = rb.read_data();
    rb.write_data(test_f);
    rb.write_data(12.4f);
    rb.write_data(300.0);
    auto f1 = static_cast<double>(rb.read_data());
    auto f2 = static_cast<double>(rb.read_data());
    auto f3 = static_cast<double>(rb.read_data());
    printf("%f/%f/%f", f1, f2, f3);
    return 0;
}
