#include <iostream>
#include "babel.hpp"
#include <windows.h>

struct A{
    int a;
};
struct B : virtual A{
    int b;
};
struct C : virtual A{
    int c;
};
struct D: public B, public C{
    int d;
};
int main()
{
    D d;
    d.B::a = 12;
    d.C::a = 222;
    std::cout << d.B::a << '\n' << d.C::a;
    return 0;
}
