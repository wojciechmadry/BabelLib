#ifndef TESTS_REQUEST_HPP
#define TESTS_REQUEST_HPP

#include "babel.hpp"

namespace TESTING{
    void REQUEST_HPP() //DONE
    {
        babel::REQ::request req;
        assert(!req.has_request() && req.is_empty() && req.request_size() == 0);
        req.clear();
        int p = 0;
        req.send_req([]() { return 33; }, &p);
        req.send_req([]() { return 37; }, &p);
        assert(req.has_request() && !req.is_empty() && req.request_size() == 2);
        req.pop();
        assert(req.has_request() && !req.is_empty() && req.request_size() == 1);
        req.call();
        assert(!req.has_request() && req.is_empty() && req.request_size() == 0);
        assert(p == 37);
        req.call_all();
        req.pop_n_if_possible(100);
        std::unique_ptr<int> pq;
        req.send_req([]() { return std::make_unique<int>(13); }, &pq);
        req.call_if_possible();
        assert(*pq == 13);
        req.send_req([](const std::unique_ptr<int> &uq) { return std::make_unique<int>(( *uq ) * 2); }, &pq, pq);
        req.call_n(1);
        assert(*pq == 26);
    }
}

#endif  // TESTS_REQUEST_HPP
