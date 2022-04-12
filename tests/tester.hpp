//
// Created by Wojtek on 08.04.2021.
//

#ifndef CLIONPROJECT_TESTER_HPP
#define CLIONPROJECT_TESTER_HPP

#include "babel.hpp"

// Tests
#include "char/const_char/const_char.hpp"
#include "char/char/char.hpp"
#include "wrapper/wrapper.hpp"
#include "variadic/variadic.hpp"
#include "time/time.hpp"
#include "optional/optional.hpp"
#include "algorithm/math/math.hpp"
#include "file_system/file_system.hpp"
#include "any/void_any.hpp"
#include "any/pol_any.hpp"
#include "algorithm/algorithm/algorithm.hpp"
#include "system/windows/windows.hpp"
#include "request/request/request.hpp"
#include "text/text.hpp"
#include "concepts/concepts/concepts.hpp"
#include "container/dynamic_array/dynamic_array.hpp"
#include "container/list/list.hpp"
#include "iterators/enumerate/enumerate.hpp"
#include "iterators/range/range.hpp"
#include "iterators/write_read/write_read.hpp"
#include "algorithm/crypt/sha/sha.hpp"
#include "tokens/tokens.hpp"
#include "container/ringbuffer/ringbuffer.hpp"

namespace TESTING{

    void START_ALL_TEST(const int times = 1)
    {
        auto start_test = []() {
           RINGBUFFER_HPP();
            SHA_HASH_TEST();
            RANGES_ITERATOR();
            ENUMERATE_ITERATOR();
            LIST_HPP();
            DYNAMIC_ARRAY_HPP();
            CONCEPT_HPP();
            TEXT_HPP();
            WRAPER_HPP();
            VARIADIC_HPP();
            TIME_HPP();
            OPTIONAL_HPP();
            MATH_HPP();
            if ( babel::COMPILER_IS_64B ) //NOLINT //TODO on 32 bit clang compiler, cant see files
            {
                FILE_SYSTEM_HPP();
                WRITER_READER_ITERATOR();
            }
            CHAR_HPP();
            ALGORITHM_HPP();
            TOKENS_HPP();
            CONST_CHAR_HPP();
#ifdef _WIN32
            WINDOWSCONV_HPP();
#endif
           // REQUEST_HPP();

            //ANY_HPP_VOID_ANY();
            //ANY_HPP_POLY_ANY();
        };
        if ( times <= 0 )
        {
            while ( 1 ) // NOLINT
                start_test();
        } else
        {
            for ( int i = 0 ; i < times ; ++i )
                start_test();
        }

    }
}

#endif //CLIONPROJECT_TESTER_HPP
