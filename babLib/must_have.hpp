#ifndef BABEL_MUST_HAVE
#define BABEL_MUST_HAVE

#include <string>
#include <chrono>
#include <algorithm>
#include <functional>
#include <utility>
#include <variant>
#include "concepts/concepts.hpp"

#include "typdef.hpp"

//THREAD
#include <thread>
#include <mutex>
#include <condition_variable>

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
#include <random>

// CONTAINER
#include "container/container.hpp"


#ifdef _WIN32
    #include <windows.h>
#elif linux //TODO Need check if it works
    #include <unistd.h>
#endif


namespace babel{
    static constexpr const char *VERSION = "1.26";
    static constexpr const bool COMPILER_IS_64B = ( sizeof(void *) == 8 ); //NOLINT
    static constexpr const bool COMPILER_IS_32B = ( sizeof(void *) == 4 ); //NOLINT
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
        static const constexpr std::array<std::uint64_t, 80> PRIME_SHA_ARRAY_64 = {
                0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
                0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
                0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
                0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
                0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
                0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
                0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
                0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
                0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
                0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
                0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
                0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
                0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
                0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
                0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
                0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
                0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
                0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
                0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
                0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
        };

        static const constexpr std::array<std::uint32_t, 80> PRIME_SHA_ARRAY_32 = {
                0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
                0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
                0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
                0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
                0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
                0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
                0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
                0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
                0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
                0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
                0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
                0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
                0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
                0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
                0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
        };

        template< typename INT, std::size_t MAX_BIT = sizeof(INT) * 8 >
        class INT_HOLDER
        {
            std::vector<INT> _holder;
            std::size_t nob = 0;
            INT data = 0;

            void push_data() noexcept
            {
                _holder.emplace_back(data);
                data = 0;
            }

            void check_data_full() noexcept
            {
                if ( nob % MAX_BIT == 0 )
                    push_data();
            }

            void push_bit(const bool _bit) noexcept
            {
                data |= ( static_cast<INT>(_bit) << ( ( sizeof(INT) * 8 - 1 ) - ( nob % MAX_BIT ) ) );
                ++nob;
                check_data_full();
            }

        public:
            [[nodiscard]] std::vector<INT> &&get_vec() noexcept
            {
                return std::move(_holder);
            }

            template< typename ToPush >
            requires(std::is_same_v<std::decay_t<ToPush>, bool>)
            void push(ToPush
            DATA) noexcept
            {
                push_bit(DATA);
            }

            template< typename ToPush >
            requires ( !std::is_same_v<std::decay_t<ToPush>, bool> )
            void push(ToPush DATA) noexcept
            {

                if constexpr( sizeof(ToPush) > sizeof(INT) )
                {
                    for ( std::int64_t i = sizeof(ToPush) * 8 - sizeof(INT) * 8 ; i >= 0 ; i -= sizeof(INT) * 8 )
                    {
                        push(static_cast<INT>(DATA >> i));
                    }

                } else
                {
                    auto fulled = nob % MAX_BIT;
                    auto space = MAX_BIT - fulled;

                    if ( space >= sizeof(ToPush) * 8 )
                    {
                        auto CASTED_DATA = static_cast<INT>(DATA);
                        auto SHIFT = MAX_BIT - sizeof(ToPush) * 8 - fulled;
                        CASTED_DATA = CASTED_DATA << SHIFT;
                        data |= CASTED_DATA;
                        nob += sizeof(ToPush) * 8;
                        check_data_full();
                        return;
                    } else
                    {
                        for ( int64_t i = ( sizeof(ToPush) * 8 - 1 ) ; i >= 0 ; --i )
                        {
                            push_bit(static_cast<bool>(DATA & ( static_cast<ToPush>(1) << i )));
                        }
                    }
                }


            }

            [[nodiscard]] auto number_of_bits() const noexcept
            {
                return nob;
            }
        };

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

