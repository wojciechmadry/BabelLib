#ifndef BABEL_SHA_512
#define BABEL_SHA_512

#include "../../../must_have.hpp"

namespace babel::ALGO::CRYPT{
    std::string sha512(const std::string &HASH) noexcept
    {
        using WORD = babel::CONCEPTS::type_of_number<8, false>::type;

        constexpr const WORD CHUNK_LENGTH = 1024;
        constexpr const WORD ROUNDS = 80;

        assert(sizeof(WORD) == 8);

       constexpr const auto& K = _BABEL_PRIVATE_DO_NOT_USE::_PRIVATE_BABEL::PRIME_SHA_ARRAY_64;

        std::array<WORD, 8> H = {
                0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
                0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
        };


        auto len = HASH.size() << 3;
        _BABEL_PRIVATE_DO_NOT_USE::_PRIVATE_BABEL::INT_HOLDER<WORD> holder;
        for ( auto c : HASH )
            holder.push<int8_t>(c);
        holder.push<bool>(true);
        while ( holder.number_of_bits() % CHUNK_LENGTH != 896 )
            holder.push<bool>(false);
        holder.push<uint64_t>(0);
        holder.push<uint64_t>(len);

        std::vector<WORD> MSG = holder.get_vec();

        std::array<WORD, ROUNDS> w {0};
        std::size_t i;

        for ( auto iterator = std::begin(MSG) ; iterator < std::end(MSG) ; iterator += 16 )
        {
            std::copy(iterator, iterator + 16, w.begin());

            for ( i = 16 ; i < ROUNDS ; ++i )
            {
                auto s0 = std::rotr(w[i - 15], 1) ^ std::rotr(w[i - 15], 8) ^ ( w[i - 15] >> 7 );
                auto s1 = std::rotr(w[i - 2], 19) ^ std::rotr(w[i - 2], 61) ^ ( w[i - 2] >> 6 );

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
                auto s1 = std::rotr(e, 14) ^ std::rotr(e, 18) ^ std::rotr(e, 41);
                auto ch = ( e & f ) ^ ( ( ~e ) & g );
                auto s0 = std::rotr(a, 28) ^ std::rotr(a, 34) ^ std::rotr(a, 39);
                auto temp1 = h + s1 + ch + K[i] + w[i];
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
        res.reserve(512);
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

