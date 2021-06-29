#ifndef BABEL_SHA_224
#define BABEL_SHA_224

#include "../../../must_have.hpp"
#include "../../../iterators/iterator.hpp"

namespace babel::ALGO::CRYPT{
    std::string sha224(const std::string &HASH) noexcept
    {

        using WORD = babel::CONCEPTS::type_of_number<4, false>::type;

        assert(sizeof(WORD) == 4);

        static const constexpr std::array<WORD, 64> K = {
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

        std::array<WORD, 8> H = {
                0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
                0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4
        };

        auto right_rotate = [](const WORD n, const WORD d) -> WORD {
            return ( n >> d ) | ( n << ( 32 - d ) );
        };

        auto to_bits = [](const std::string &MSG) {
            std::string bits;
            bits.reserve(( MSG.size() << 3 ) + 1);
            for ( auto c : MSG )
                bits += std::bitset<8>(c).to_string();
            return bits;
        };

        auto tb = to_bits(HASH);
        auto len = tb.size();
        tb.push_back('1');
        while ( tb.size() % 512 != 448 )
            tb.push_back('0');
        tb += std::bitset<64>(len).to_string();

        std::array<WORD, 64> w {0};
        std::size_t i;
        auto CHUNK = babel::ITERATOR::range<std::size_t, std::size_t>(0, 512, 32);

        for ( auto start : babel::ITERATOR::range<std::size_t, std::size_t>(0, tb.size(), 512) )
        {
            CHUNK.Start() = start;
            CHUNK.Stop() = start + 512;
            std::transform(CHUNK.begin(), CHUNK.end(), w.begin(),
                           [&tb](const auto chunk) {
                               WORD res {0};
                               for ( std::size_t i = chunk ; i < chunk + 32 ; ++i )
                               {
                                   if ( tb[i] == '1' )
                                   {
                                       res += 1 << ( 31 - ( i - chunk ) );
                                   }
                               }
                               return res;
                           });

            for ( i = 16 ; i < 64 ; ++i )
            {
                auto s0 = right_rotate(w[i - 15], 7) ^ right_rotate(w[i - 15], 18) ^ ( w[i - 15] >> 3 );
                auto s1 = right_rotate(w[i - 2], 17) ^ right_rotate(w[i - 2], 19) ^ ( w[i - 2] >> 10 );

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


            for ( i = 0 ; i < 64 ; ++i )
            {
                auto s1 = right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
                auto ch = ( e & f ) ^ ( ( ~e ) & g );
                auto temp1 = h + s1 + ch + K[i] + w[i];
                auto s0 = right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
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
        res.reserve(224);
        for ( i = 0 ; i < H.size() - 1 ; ++i )
        {
            std::stringstream stream;
            stream << std::hex << H[i];
            res += stream.str();
        }

        return res;
    }
}
#endif
