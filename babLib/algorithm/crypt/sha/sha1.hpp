#ifndef BABEL_SHA_1
#define BABEL_SHA_1

#include "../../../must_have.hpp"
#include "../../../iterators/iterator.hpp"

namespace babel::ALGO::CRYPT{
    std::string sha1(const std::string &HASH) noexcept
    {
        using WORD = babel::CONCEPTS::type_of_number<4, false>::type;

        constexpr const WORD CHUNK_LENGTH = 512;
        constexpr const WORD ROUNDS = 80;

        assert(sizeof(WORD) == 4);

        std::array<WORD, 5> H = {
                0x67452301, 0xEFCDAB89,
                0x98BADCFE, 0x10325476,
                0xC3D2E1F0
        };

        auto to_bits = [](const std::string &MSG) {
            std::string bits;
            bits.reserve(( MSG.size() << 3 ) + 1);
            for ( auto c : MSG )
                bits += std::bitset<8>(c).to_string();
            return bits;
        };

        auto len = HASH.size() << 3;

        auto tb = to_bits(HASH);
        tb.push_back('1');
        while ( tb.size() % CHUNK_LENGTH != 448 )
            tb.push_back('0');
        tb += std::bitset<64>(len).to_string();

        std::array<WORD, ROUNDS> w {0};
        std::size_t i;
        auto CHUNK = babel::ITERATOR::range<std::size_t, std::size_t>(0, CHUNK_LENGTH, sizeof(WORD) * 8);

        for ( auto start : babel::ITERATOR::range<std::size_t, std::size_t>(0, tb.size(), CHUNK_LENGTH) )
        {
            CHUNK.Start() = start;
            CHUNK.Stop() = start + CHUNK_LENGTH;
            std::transform(CHUNK.begin(), CHUNK.end(), w.begin(),
                           [&tb](const auto chunk) {
                               WORD res {0};
                               for ( std::size_t i = chunk ; i < chunk + sizeof(WORD) * 8 ; ++i )
                               {
                                   if ( tb[i] == '1' )
                                   {
                                       res += 1 << ( (sizeof(WORD) * 8 - 1) - ( i - chunk ) );
                                   }
                               }
                               return res;
                           });

            for(i = 16 ; i < ROUNDS ; ++i)
            {
                w[i] = std::rotl(w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16], 1);
            }

            auto a = H[0];
            auto b = H[1];
            auto c = H[2];
            auto d = H[3];
            auto e = H[4];

            decltype(e) f, k;

            for (i = 0 ; i < ROUNDS ; ++i)
            {
                if (i <= 19)
                {
                    f = (b & c) | ((~b) & d);
                    k = 0x5A827999;
                }
                else if (i <= 39)
                {
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                }
                else if (i <= 59)
                {
                    f = (b & c) | (b & d) | (c & d);
                    k = 0x8F1BBCDC;
                }
                else
                {
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                }

                auto temp = std::rotl(a, 5) + f + e + k + w[i];
                e = d;
                d = c;
                c = std::rotl(b, 30);
                b = a;
                a = temp;
            }

            H[0] += a;
            H[1] += b;
            H[2] += c;
            H[3] += d;
            H[4] += e;
        }

        std::string res;
        res.reserve(160);
        for ( auto h : H )
        {
            std::stringstream stream;
            stream << std::hex << h;
            res += stream.str();
        }

        return res;
    }
}

#endif