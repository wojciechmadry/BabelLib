#include <iostream>
#include "babel.hpp"


int main()
{
    babel::GRAPHICS::rgb r(0, 0, 255);
    auto c = babel::GRAPHICS::RGB_TO_CMYK(r);
    std::cout << (int) c[0] << '\n';
    std::cout << (int) c[1] << '\n';
    std::cout << (int) c[2] << '\n';
    std::cout << (int) c[3] << '\n';
	std::cin.get();
	std::cin.get();
	babel::REQ::request req;
	auto func = []()->void{std::cout<<"TEST";};
	req.send_req(func, nullptr);
	req.call_all();
    return 0;
}
