#ifndef TESTS_RINGBUFFER_HPP
#define TESTS_RINGBUFFER_HPP

#include "babel.hpp"
#include <cassert>

namespace TESTING{
    void RINGBUFFER_HPP()
    {
        int test_f = 3;
        babel::CONTAINER::RingBuffer<int, 2> rb;
        rb.write_data(test_f);
        rb.write_data(12);
        auto f1 = rb.read_data().data;
        rb.write_data(300);
        auto f2 = rb.read_data().data;
        auto f3 = rb.read_data().data;
        assert(f1 == 3);
        assert(f2 == 12);
        assert(f3 == 300);
        rb.write_data(100);
        rb.write_data(200);
        rb.write_data(300);
        f1 = rb.read_data().data;
        f2 = rb.read_data().data;
        assert(f1 == 100);
        assert(f2 == 200);
        assert(!rb.read_data().isValid);
        assert(rb.is_safe_mode());

        babel::CONTAINER::RingBuffer<int, 2, false> ns;
        assert(!ns.is_safe_mode());
        ns.write_data(100);
        ns.write_data(200);
        ns.write_data(300);
        f1 = ns.read_data().data;
        f2 = ns.read_data().data;
        assert(f1 == 300);
        assert(f2 == 200);
    }
}

#endif  // TESTS_RINGBUFFER_HPP
