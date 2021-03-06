// Copyright [2021] <Wojtek>"
#ifndef BABLIB_ALGORITHM_CRYPT_SHA_SHA224_HPP_
#define BABLIB_ALGORITHM_CRYPT_SHA_SHA224_HPP_

#include "sha_array.hpp"
#include <string>
#include "../../../concepts/concepts.hpp"
#include <bit>
#include "../../cast.hpp"

namespace babel::ALGO::CRYPT{
    inline std::string sha224(const std::string &HASH) noexcept
    {
        using WORD = babel::CONCEPTS::type_of_number<4, false>::type;

        constexpr const WORD CHUNK_LENGTH = 512;
        constexpr const WORD ROUNDS = 64;

        static_assert(sizeof(WORD) == 4);

        constexpr const auto &K = BABEL_PRIVATE_DO_NOT_USE::PRIVATE_BABEL::PRIME_SHA_ARRAY_32;

        std::array<WORD, 8> H = {
                0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
                0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
        };


        auto len = HASH.size() << 3;
        BABEL_PRIVATE_DO_NOT_USE::PRIVATE_BABEL::INT_HOLDER<WORD> holder;
        for ( auto c : HASH )
            holder.push<int8_t>(c);
        holder.push<bool>(true);
        while ( holder.number_of_bits() % CHUNK_LENGTH != 448 )
            holder.push<bool>(false);
        holder.push<uint64_t>(len);

        std::vector<WORD> MSG = holder.get_vec();

        std::array<WORD, ROUNDS> w {0};
        std::size_t i;

        for ( auto iterator = std::begin(MSG) ; iterator < std::end(MSG) ; iterator += 16 )
        {
            std::copy(iterator, iterator + 16, w.begin());

            for ( i = 16 ; i < ROUNDS ; ++i )
            {
                auto s0 = std::rotr(w[i - 15], 7) ^ std::rotr(w[i - 15], 18) ^ ( w[i - 15] >> 3 );
                auto s1 = std::rotr(w[i - 2], 17) ^ std::rotr(w[i - 2], 19) ^ ( w[i - 2] >> 10 );

                w[i] = w[i - 16] + s0 + w[i - 7] + s1;
            }

            auto a = H[0];
            auto b = H[1];
            auto c = H[2];
            auto d = H[3];
            auto e = H[4];
            auto f = H[5];
            auto g = H[6];
            auto h = H[7];


            for ( i = 0 ; i < ROUNDS ; ++i )
            {
                auto s1 = std::rotr(e, 6) ^ std::rotr(e, 11) ^ std::rotr(e, 25);
                auto ch = ( e & f ) ^ ( ( ~e ) & g );
                auto temp1 = h + s1 + ch + K[i] + w[i];
                auto s0 = std::rotr(a, 2) ^ std::rotr(a, 13) ^ std::rotr(a, 22);
                auto maj = ( a & b ) ^ ( a & c ) ^ ( b & c );
                auto temp2 = s0 + maj;
                h = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }

            H[0] += a;
            H[1] += b;
            H[2] += c;
            H[3] += d;
            H[4] += e;
            H[5] += f;
            H[6] += g;
            H[7] += h;
        }

        std::string res;
        res.reserve(56);
        for ( i = 0 ; i < H.size() - 1 ; ++i )
        {
            res += babel::ALGO::CAST::to_hex(H[i]);
        }

        return res;
    }  // namespace babel::ALGO::CRYPT
}
#endif  // BABLIB_ALGORITHM_CRYPT_SHA_SHA224_HPP_
