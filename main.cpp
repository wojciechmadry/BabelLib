#include <iostream>
#include "babel.hpp"
#include "tester.hpp"
#include <cassert>

babel::TOKEN::tokenizer tokens(5);



void sum_vec(int64_t& sum, std::size_t& pos, const std::vector<int>& num)
{

    while(pos < num.size())
    {
        auto Token = tokens.get_token(0);
        (void) Token;
        if (pos >= num.size())
        {
            break;
        }
        sum += num[pos];
        ++pos;
    }

}

int main()
{


    std::cout << "Compiler is 64bit ? : " << babel::COMPILER_IS_64B << '\n';
    std::cout << "BABEL VERSION : " << babel::VERSION << '\n';
    //auto T = babel::TIME::measure_time(1, TESTING::START_ALL_TEST, 1);
    //std::cout << "Done\nTime : " << T << " seconds\n";

    for(int ik = 0 ; ik < 100 ; ++ik)
    {
        std::vector<int> to_sum(10000);
        for(auto& Element : to_sum)
        {
            Element = babel::ALGO::MATH::random_generator::generate<int>(-500,500);
        }
        int64_t sum = std::accumulate(to_sum.begin(), to_sum.end(), 0);
        std::vector<std::thread> vec;
        std::size_t i = 0;
        int64_t sum_token = 0;
        for(std::size_t j = 0 ; j < 10 ; ++j)
        {
            vec.emplace_back(sum_vec, std::ref(sum_token), std::ref(i), std::ref(to_sum));
        }
        for(auto& th : vec)
            th.join();
        //std::cout << "SUM = " << sum << ", SUM_TOKEN = " << sum_token << "\n";
        assert(sum == sum_token);

    }

    return 0;
}
