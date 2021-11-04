#ifndef TESTS_CONCEPTS_HPP
#define TESTS_CONCEPTS_HPP

#include "babel.hpp"

namespace TESTING{
    void CONCEPT_HPP()
    {
        assert(!babel::CONCEPTS::IS_ANY_POINTER<int>);
        assert(babel::CONCEPTS::IS_ANY_POINTER<int *>);
        assert(babel::CONCEPTS::IS_ANY_POINTER<std::unique_ptr<int>>);
        assert(babel::CONCEPTS::IS_ANY_POINTER<std::shared_ptr<int>>);
        assert(babel::CONCEPTS::IS_ANY_POINTER<std::weak_ptr<int>>);
        assert(!babel::CONCEPTS::IS_ANY_POINTER<std::vector<int>>);
        assert(!babel::CONCEPTS::IS_ANY_POINTER<std::vector<int *>>);
        assert(!babel::CONCEPTS::IS_ANY_POINTER<std::string>);
        assert(!babel::CONCEPTS::IS_ANY_POINTER<std::reference_wrapper<int>>);
        assert(babel::CONCEPTS::IS_ANY_POINTER<std::reference_wrapper<int *>>);
    }
}

#endif  // CONCEPTS
