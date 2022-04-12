#ifndef TESTS_LIST_HPP
#define TESTS_LIST_HPP

#include "babel.hpp"

namespace TESTING{
    void LIST_HPP()
    {
        using namespace babel::CONTAINER;
        list<int> l;
        assert(l.size() == 0);
        l.push_back(5);
        assert(l.size() == 1 && l[0] == 5);
        l.push_back(10);
        assert(l.size() == 2 && l[0] == 5 && l[1] == 10);
        l.push_back(20);
        assert(l.size() == 3 && l[0] == 5 && l[1] == 10 && l[2] == 20);
        l.clear();
        assert(l.size() == 0);
        l.push_front(10);
        assert(l.size() == 1 && l[0] == 10);
        l.push_front(12);
        assert(l.size() == 2 && l[0] == 12 && l[1] == 10);
        l.push_front(13);
        assert(l.size() == 3 && l[0] == 13 && l[1] == 12 && l[2] == 10);
        l.clear();
        assert(l.size() == 0);
        list<int> ll(15, 5);
        assert(ll[0] == 5 && ll[14] == 5 && ll.size() == 15);
        l = list<int>({1, 2, 3, 4, 5});
        assert(l.size() == 5 && l[0] == 1 && l[4] == 5);
        l.pop_back();
        assert(l[3] == 4);
        l.pop_back();
        assert(l[2] == 3);
        l.pop_back();
        assert(l[1] == 2);
        l.pop_back();
        assert(l[0] == 1);
        l.pop_back();
        assert(l.size() == 0);
        l = list<int>({1, 2, 3, 4, 5});
        l.pop_front();
        assert(l[0] == 2);
        l.pop_front();
        assert(l[0] == 3);
        l.pop_front();
        assert(l[0] == 4);
        l.pop_front();
        assert(l[0] == 5);
        l.pop_front();
        assert(l.size() == 0);
        l = list<int>({1, 2, 3, 4, 5});
        assert(*l.find(5) == 5);
        assert(*l.find(2) == 2);
        assert(l.find(312) == nullptr);
        assert(*l.find([](int my_i) { return my_i > 3; }) == 4);
        assert(l.find([](int my_i) { return my_i > 30; }) == nullptr);
        l[0] = 12;
        assert(l[0] == 12);
        ll = l;
        assert(ll[0] == 12 && ll[4] == 5 && ll.size() == 5);
        l = list<int>({1, 2, 3});
        l.remove(2);
        assert(l.size() == 2 && l[0] == 1 && l[1] == 3);
        ll = l;
        l.remove(1);
        ll.remove(3);
        assert(l.size() == 1 && ll.size() == 1);
        assert(l[0] == 3 && ll[0] == 1);
        l.remove(3);
        ll.remove(1);
        assert(l.size() == 0 && ll.size() == 0);
        l.push_back(2);
        l.push_front(4);
        l.push_back(3);
        assert(l.size() == 3 && l[0] == 4 && l[1] == 2 && l[2] == 3);
        l.remove([](int y) { return y == 3; });
        assert(l.size() == 2 && l[0] == 4 && l[1] == 2);
        l.remove([](int y) { return y == 3; });
        assert(l.size() == 2);
        l.clear();
        l = {1, 2, 3};
        assert(l.size() == 3 && l[0] == 1 && l[1] == 2 && l[2] == 3);
        l.clear();
        for ( int i = 10 ; i >= 0 ; --i )
            l.push_in_order(i, std::greater<>());
        for ( int i = 0 ; i < 10 ; ++i )
            assert(l[static_cast<std::size_t>(i)] == i);
        l.clear();
        for ( std::size_t i = 0 ; i < 10 ; ++i )
        {
            l.push_in_order(static_cast<int>(i), std::greater<>());
            assert(l[i] == static_cast<int>(i));
        }
        l.clear();
        for ( int i = 0 ; i < 10 ; ++i )
            l.push_in_order(i, std::less<>());
        for ( int i = 9 ; i >= 0 ; --i )
            assert(l[static_cast<std::size_t>(9 - i)] == i);
        l.clear();
        babel::ALGO::MATH::random_generator rg;
        for ( std::size_t i = 0 ; i < 10000 ; ++i )
            l.push_in_order(rg.generate(0, 100000), std::greater<>());
        for ( std::size_t i = 0 ; i < 10000 - 1 ; ++i )
            assert(l[i + 1] >= l[i]);
        l.clear();
        for ( int i = 0 ; i < 100000 ; ++i )
            l.push_back(i);
        l.clear();
        l.push_back({3, 1, 2});
        assert(l.size() == 3 && l[0] == 3 && l[1] == 1 && l[2] == 2);
        l.clear();
        l.push_back({1, 1, 1, 1, 1, 1, 1, 1, 1});
        for ( auto el : l )
            assert(el == 1);
        l.clear();
        l.push_back(1);
        assert(l.size() == 1 && l[0] == 1);
        l.remove(1);
        assert(l.size() == 0);
        l.push_front(1);
        assert(l.size() == 1 && l[0] == 1);
        l.remove(1);
        assert(l.size() == 0);
        l.push_front(5);
        l.push_back(2);
        assert(l.size() == 2 && l[1] == 2 && l[0] == 5);
        l.remove(2);
        assert(l.size() == 1 && l[0] == 5);
        l.remove(5);
        assert(l.size() == 0);
        l.push_front(5);
        l.push_back(2);
        l.remove(5);
        assert(l.size() == 1 && l[0] == 2);
        l.remove(2);
        assert(l.size() == 0);
    }
}

#endif  // TESTS_LIST_HPP
