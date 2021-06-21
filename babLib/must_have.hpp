#ifndef BABEL_MUST_HAVE
#define BABEL_MUST_HAVE

#include <chrono>
#include <functional>
#include <utility>
#include <variant>
#include "concepts/concepts.hpp"
#include <thread>


//FILE OPERATION
#include <fstream>
#include <filesystem>

//EXCEPTION, ASSERTS
#include <cassert>
#include <stdexcept>

// MATH - NUMBER
#include <random>
#include <numeric>
#include <complex>
#include <numbers>
#include <cmath>

// CONTAINER
#include <list>
#include <queue>
#include "container/list.hpp"
#include "container/dynamic_array.hpp"

#ifdef _WIN32
    #include <Windows.h>
#endif

#ifndef i64
#define i64 int64_t
#endif

#ifndef i32
#define i32 int32_t
#endif

#ifndef i16
#define i16 int16_t
#endif

#ifndef i8
#define i8 int8_t
#endif

#ifndef u64
#define u64 uint64_t
#endif

#ifndef u32
#define u32 uint32_t
#endif

#ifndef u16
#define u16 uint16_t
#endif

#ifndef u8
#define u8 uint8_t
#endif


#ifndef float32
#define float32 float
#endif

#ifndef float64
#define float64 double
#endif

#ifndef float128
#define float128 long double
#endif


namespace babel
{
    static constexpr const char* VERSION = "1.19";
    static constexpr const bool COMPILER_IS_64B = (sizeof(void*) == 8); //NOLINT
    static constexpr const bool COMPILER_IS_32B = (sizeof(void*) == 4); //NOLINT
}

namespace _BABEL_PRIVATE_DO_NOT_USE //NOLINT
{


    class _PRIVATE_BABEL //NOLINT
    {
        static constexpr void babel_mult(uint64_t F[2][2], uint64_t M[2][2]) noexcept
        {
            uint64_t x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
            uint64_t y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
            uint64_t z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
            uint64_t w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
            F[0][0] = x;
            F[0][1] = y;
            F[1][0] = z;
            F[1][1] = w;
        }

    public:

        static constexpr void babel_pow(uint64_t F[2][2], unsigned n) noexcept
        {
            if ( n < 2 )
                return;
            babel_pow(F, n >> 1u);
            babel_mult(F, F);
            if ( n % 2 != 0 )
            {
                uint64_t x = F[0][0] + F[0][1];
                uint64_t z = F[1][0] + F[1][1];
                F[0][1] = F[0][0];
                F[0][0] = x;
                F[1][1] = F[1][0];
                F[1][0] = z;
            }
        }
    };
}
#endif

