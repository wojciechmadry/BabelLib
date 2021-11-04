#ifndef TESTS_CONST_CHAR_HPP
#define TESTS_CONST_CHAR_HPP
#include "babel.hpp"



constexpr bool test_iterator()
{
    using namespace babel::CHAR;
    bool good = true;
    constexpr const_char cc("Test");

// FORWARD ITERATOR
    // First test
    {
        auto begin = cc.begin();
        auto end = cc.end();
        std::size_t i = 0;
        for(;begin!=end; ++begin, ++i)
        {
            if (*begin != cc[i])
            {
                good = false;
            }
        }

        if (i != 4)
        {
            good = false;
        }
    }


    // Second test
    {
        auto begin = cc.begin();
        std::size_t i = 0;
        while(begin != cc.end())
        {
            if (*begin != cc[i])
            {
                good = false;
            }
            ++begin;
            ++i;
        }
    }

    // Third test
    {
        auto begin = cc.begin();
        std::size_t i = 0;
        if (*(begin + 2) != 's')
        {
            good = false;
        }
        if (*(begin + 3) != 't')
        {
            good = false;
        }

        begin += 1;

        if (*begin != 'e')
        {
            good = false;
        }

        if (*(begin - 1) != 'T')
        {
            good = false;
        }

        begin -= 1;

        if (*begin != 'T')
        {
            good = false;
        }
    }

    // Fourth test
    {
        auto begin = cc.begin();
        auto end = cc.end();
        std::size_t i = 0;
        for(;!(begin==end); ++begin, ++i)
        {
            if (*begin != cc[i])
            {
                good = false;
            }
        }
    }

// REVERSE ITERATOR

    // First test
    {
        auto rbegin = cc.rbegin();
        auto rend = cc.rend();
        std::int64_t i = 3;
        for(;rbegin!=rend; ++rbegin, --i)
        {
            if (*rbegin != cc[static_cast<std::size_t>(i)])
            {
                good = false;
            }
        }
        if (i != -1)
        {
            good = false;
        }
    }

    // Second test
    {
        auto rbegin = cc.rbegin();
        std::int64_t i = 3;
        while(rbegin != cc.rend())
        {
            if (*rbegin != cc[static_cast<std::size_t>(i)])
            {
                good = false;
            }
            ++rbegin;
            --i;
        }
    }

    // Third test
    {
        auto rbegin = cc.rbegin();
        if (*(rbegin + 2) != 'e')
        {
            good = false;
        }
        if (*(rbegin + 3) != 'T')
        {
            good = false;
        }

        rbegin += 1;

        if (*rbegin != 's')
        {
            good = false;
        }

        if (*(rbegin - 1) != 't')
        {
            good = false;
        }

        rbegin -= 1;

        if (*rbegin != 't')
        {
            good = false;
        }
    }

    // Fourth test
    {
        auto rbegin = cc.rbegin();
        auto rend = cc.rend();
        std::int64_t i = 3;
        for(;!(rbegin==rend); ++rbegin, --i)
        {
            if (*rbegin != cc[static_cast<uint64_t>(i)])
            {
                good = false;
            }
        }
    }
    return good;
}

constexpr std::array<const babel::CHAR::const_char, 56> generate_dec() noexcept
{
    using namespace babel::CHAR;
    std::array<const const_char, 56> ar {
            const_char("124"), // case 1
            const_char("0124"), // case 1a
            const_char("-124"), // case 2
            const_char("-0124"), // case 2a
            const_char("-124.8"), // case 3
            const_char("-0124.8"), // case 3a
            const_char("124.8"), // case 4
            const_char("0124.8"), // case 4a
            const_char("124.8fdsgs"), // case 5
            const_char("0124.8fdsgs"), // case 5a
            const_char("-124.8fdsgs"), // case 6
            const_char("-0124.8fdsgs"), // case 6a
            const_char("22afs"), // case 7
            const_char("022afs"), // case 7a
            const_char("-22afs"), // case 8
            const_char("-022afs"), // case 8a
            const_char("-0"), // case 9
            const_char("-00"), // case 9a
            const_char("0"), // case 10
            const_char("00"), // case 10a
            const_char("025"), // case 11
            const_char("0025"), // case 11a
            const_char("-025"), // case 12
            const_char("-0025"), // case 12a
            const_char("9223372036854775807"), // case i64Max
            const_char("09223372036854775807"), // case i64Maxa
            const_char("-9223372036854775808"), // case i64Min
            const_char("-09223372036854775808"), // case i64Mina
            const_char("2147483647"), // case i32Max
            const_char("02147483647"), // case i32Maxa
            const_char("-2147483648"), // case i32Min
            const_char("-02147483648"), // case i32Mina
            const_char("32767"), // case i16Max
            const_char("032767"), // case i16Maxa
            const_char("-32768"), // case i16Min
            const_char("-032768"), // case i16Mina
            const_char("127"), // case i8Max
            const_char("0127"), // case i8Maxa
            const_char("-128"), // case i8Min
            const_char("-0128"), // case i8Mina
            const_char("18446744073709551615"), // case u64Max
            const_char("018446744073709551615"), // case u64Maxa
            const_char("0"), // case u64Min
            const_char("00"), // case u64Mina
            const_char("4294967295"), // case u32Max
            const_char("04294967295"), // case u32Maxa
            const_char("0"), // case u32Min
            const_char("00"), // case u32Mina
            const_char("65535"), // case u16Max
            const_char("065535"), // case u16Maxa
            const_char("0"), // case u16Min
            const_char("00"), // case u16Mina
            const_char("255"), // case u8Max
            const_char("0255"), // case u8Maxa
            const_char("0"), // case u8Min
            const_char("00"), // case u8Mina
    };
    return ar;
}

constexpr std::array<const babel::CHAR::const_char, 56> generate_hex() noexcept
{
    using namespace babel::CHAR;
    std::array<const const_char, 56> ar {
            const_char("7c"), // case 1
            const_char("0x7c"), // case 1a
            const_char("-7C"), // case 2
            const_char("-0x7C"), // case 2a
            const_char("-7c.8"), // case 3
            const_char("-0x7c.8"), // case 3a
            const_char("7C.8"), // case 4
            const_char("0x7C.8"), // case 4a
            const_char("7c.8fdsgs"), // case 5
            const_char("0x7c.8fdsgs"), // case 5a
            const_char("-7C.8fdsgs"), // case 6
            const_char("-0x7C.8fdsgs"), // case 6a
            const_char("16kafs"), // case 7
            const_char("0x16kafs"), // case 7a
            const_char("-16kafs"), // case 8
            const_char("-0x16kafs"), // case 8a
            const_char("-0"), // case 9
            const_char("-0x0"), // case 9a
            const_char("0"), // case 10
            const_char("0x0"), // case 10a
            const_char("019"), // case 11
            const_char("0x19"), // case 11a
            const_char("-019"), // case 12
            const_char("-0x19"), // case 12a
            const_char("7FFFFFFFFFFFFFFF"), // case i64Max
            const_char("0x7FFFFFFFFFFFFFFF"), // case i64Maxa
            const_char("-8000000000000000"), // case i64Min
            const_char("-0x8000000000000000"), // case i64Mina
            const_char("7FFFFFFF"), // case i32Max
            const_char("0x7FFFFFFF"), // case i32Maxa
            const_char("-80000000"), // case i32Min
            const_char("-0x80000000"), // case i32Mina
            const_char("7FFF"), // case i16Max
            const_char("0x7FFF"), // case i16Maxa
            const_char("-8000"), // case i16Min
            const_char("-0x8000"), // case i16Mina
            const_char("7f"), // case i8Max
            const_char("0x7f"), // case i8Maxa
            const_char("-80"), // case i8Min
            const_char("-0x80"), // case i8Mina
            const_char("FFFFFFFFFFFFFFFF"), // case u64Max
            const_char("0xFFFFFFFFFFFFFFFF"), // case u64Maxa
            const_char("0"), // case u64Min
            const_char("0x0"), // case u64Mina
            const_char("FFFFFFFF"), // case u32Max
            const_char("0xFFFFFFFF"), // case u32Maxa
            const_char("0"), // case u32Min
            const_char("0x0"), // case u32Mina
            const_char("ffff"), // case u16Max
            const_char("0xffff"), // case u16Maxa
            const_char("0"), // case u16Min
            const_char("0x0"), // case u16Mina
            const_char("ff"), // case u8Max
            const_char("0xff"), // case u8Maxa
            const_char("0"), // case u8Min
            const_char("0x0"), // case u8Mina
    };
    return ar;
}


constexpr std::array<const babel::CHAR::const_char, 56> generate_oct() noexcept
{
    using namespace babel::CHAR;
    std::array<const const_char, 56> ar {
            const_char("174"), // case 1
            const_char("0174"), // case 1a
            const_char("-174"), // case 2
            const_char("-0174"), // case 2a
            const_char("-174.8"), // case 3
            const_char("-0174.8"), // case 3a
            const_char("174.8"), // case 4
            const_char("0174.8"), // case 4a
            const_char("174.8fdsgs"), // case 5
            const_char("0174.8fdsgs"), // case 5a
            const_char("-174.8fdsgs"), // case 6
            const_char("-0174.8fdsgs"), // case 6a
            const_char("26afs"), // case 7
            const_char("026afs"), // case 7a
            const_char("-26afs"), // case 8
            const_char("-026afs"), // case 8a
            const_char("-0"), // case 9
            const_char("-00"), // case 9a
            const_char("0"), // case 10
            const_char("00"), // case 10a
            const_char("031"), // case 11
            const_char("0031"), // case 11a
            const_char("-031"), // case 12
            const_char("-0031"), // case 12a
            const_char("777777777777777777777"), // case i64Max
            const_char("0777777777777777777777"), // case i64Maxa
            const_char("-1000000000000000000000"), // case i64Min
            const_char("-01000000000000000000000"), // case i64Mina
            const_char("17777777777"), // case i32Max
            const_char("017777777777"), // case i32Maxa
            const_char("-20000000000"), // case i32Min
            const_char("-020000000000"), // case i32Mina
            const_char("77777"), // case i16Max
            const_char("077777"), // case i16Maxa
            const_char("-100000"), // case i16Min
            const_char("-0100000"), // case i16Mina
            const_char("177"), // case i8Max
            const_char("0177"), // case i8Maxa
            const_char("-200"), // case i8Min
            const_char("-0200"), // case i8Mina
            const_char("1777777777777777777777"), // case u64Max
            const_char("01777777777777777777777"), // case u64Maxa
            const_char("0"), // case u64Min
            const_char("00"), // case u64Mina
            const_char("37777777777"), // case u32Max
            const_char("037777777777"), // case u32Maxa
            const_char("0"), // case u32Min
            const_char("00"), // case u32Mina
            const_char("177777"), // case u16Max
            const_char("0177777"), // case u16Maxa
            const_char("0"), // case u16Min
            const_char("00"), // case u16Mina
            const_char("377"), // case u8Max
            const_char("0377"), // case u8Maxa
            const_char("0"), // case u8Min
            const_char("00"), // case u8Mina
    };
    return ar;
}

constexpr std::array<const babel::CHAR::const_char, 56> generate_bin() noexcept
{
    using namespace babel::CHAR;
    std::array<const const_char, 56> ar {
            const_char("1111100"), // case 1
            const_char("0b1111100"), // case 1a
            const_char("-1111100"), // case 2
            const_char("-0b1111100"), // case 2a
            const_char("-1111100.8"), // case 3
            const_char("-0b1111100.8"), // case 3a
            const_char("1111100.8"), // case 4
            const_char("0b1111100.8"), // case 4a
            const_char("1111100.8fdsgs"), // case 5
            const_char("0b1111100.8fdsgs"), // case 5a
            const_char("-1111100.8fdsgs"), // case 6
            const_char("-0b1111100.8fdsgs"), // case 6a
            const_char("10110afs"), // case 7
            const_char("0b10110afs"), // case 7a
            const_char("-10110afs"), // case 8
            const_char("-0b10110afs"), // case 8a
            const_char("-0"), // case 9
            const_char("-0b0"), // case 9a
            const_char("0"), // case 10
            const_char("0b0"), // case 10a
            const_char("011001"), // case 11
            const_char("0b011001"), // case 11a
            const_char("-011001"), // case 12
            const_char("-0b011001"), // case 12a
            const_char("111111111111111111111111111111111111111111111111111111111111111"), // case i64Max
            const_char("0b111111111111111111111111111111111111111111111111111111111111111"), // case i64Maxa
            const_char("-1000000000000000000000000000000000000000000000000000000000000000"), // case i64Min
            const_char("-0b1000000000000000000000000000000000000000000000000000000000000000"), // case i64Mina
            const_char("1111111111111111111111111111111"), // case i32Max
            const_char("0b1111111111111111111111111111111"), // case i32Maxa
            const_char("-10000000000000000000000000000000"), // case i32Min
            const_char("-0b10000000000000000000000000000000"), // case i32Mina
            const_char("111111111111111"), // case i16Max
            const_char("0b111111111111111"), // case i16Maxa
            const_char("-1000000000000000"), // case i16Min
            const_char("-0b1000000000000000"), // case i16Mina
            const_char("1111111"), // case i8Max
            const_char("0b1111111"), // case i8Maxa
            const_char("-10000000"), // case i8Min
            const_char("-0b10000000"), // case i8Mina
            const_char("1111111111111111111111111111111111111111111111111111111111111111"), // case u64Max
            const_char("0b1111111111111111111111111111111111111111111111111111111111111111"), // case u64Maxa
            const_char("0"), // case u64Min
            const_char("0b0"), // case u64Mina
            const_char("11111111111111111111111111111111"), // case u32Max
            const_char("0b11111111111111111111111111111111"), // case u32Maxa
            const_char("0"), // case u32Min
            const_char("0b0"), // case u32Mina
            const_char("1111111111111111"), // case u16Max
            const_char("0b1111111111111111"), // case u16Maxa
            const_char("0"), // case u16Min
            const_char("0b0"), // case u16Mina
            const_char("11111111"), // case u8Max
            const_char("0b11111111"), // case u8Maxa
            const_char("0"), // case u8Min
            const_char("0b0"), // case u8Mina
    };
    return ar;
}

enum class BASE
{
    DEC = 0,
    HEX = 1,
    OCT,
    BIN
};



template<typename T, BASE base>
constexpr auto integer_test() noexcept
{
    using namespace babel::CHAR;
    constexpr std::array<const std::array<const const_char, 56> , 4> arrays
            {
                    generate_dec(),
                    generate_hex(),
                    generate_oct(),
                    generate_bin()
            };
    constexpr auto id = static_cast<std::size_t>(base);
    constexpr T baseMult = (id == 0) ? 10 : (id == 1 ? 16 : (id == 2 ? 8 : 2));
    if constexpr (base == BASE::DEC)
    {
        static_assert(baseMult == 10);
    }
    if constexpr (base == BASE::HEX)
    {
        static_assert(baseMult == 16);
    }
    if constexpr (base == BASE::OCT)
    {
        static_assert(baseMult == 8);
    }
    if constexpr (base == BASE::BIN)
    {
        static_assert(baseMult == 2);
    }
    {
        constexpr const_char case1 = arrays[id][0];
        constexpr const_char case1a = arrays[id][1];
        constexpr const_char case2 = arrays[id][2];
        constexpr const_char case2a = arrays[id][3];
        constexpr const_char case3 = arrays[id][4];
        constexpr const_char case3a = arrays[id][5];
        constexpr const_char case4 = arrays[id][6];
        constexpr const_char case4a = arrays[id][7];
        constexpr const_char case5 = arrays[id][8];
        constexpr const_char case5a = arrays[id][9];
        constexpr const_char case6 = arrays[id][10];
        constexpr const_char case6a = arrays[id][11];
        constexpr const_char case7 = arrays[id][12];
        constexpr const_char case7a = arrays[id][13];
        constexpr const_char case8 = arrays[id][14];
        constexpr const_char case8a = arrays[id][15];
        constexpr const_char case9 = arrays[id][16];
        constexpr const_char case9a = arrays[id][17];
        constexpr const_char case10 = arrays[id][18];
        constexpr const_char case10a = arrays[id][19];
        constexpr const_char case11 = arrays[id][20];
        constexpr const_char case11a = arrays[id][21];
        constexpr const_char case12 = arrays[id][22];
        constexpr const_char case12a = arrays[id][23];

        constexpr const_char caseI64Max = arrays[id][24];
        constexpr const_char caseI64Maxa = arrays[id][25];
        constexpr const_char caseI64Min = arrays[id][26];
        constexpr const_char caseI64Mina = arrays[id][27];

        constexpr const_char caseI32Max = arrays[id][28];
        constexpr const_char caseI32Maxa = arrays[id][29];
        constexpr const_char caseI32Min = arrays[id][30];
        constexpr const_char caseI32Mina = arrays[id][31];


        constexpr const_char caseI16Max = arrays[id][32];
        constexpr const_char caseI16Maxa = arrays[id][33];
        constexpr const_char caseI16Min = arrays[id][34];
        constexpr const_char caseI16Mina = arrays[id][35];

        constexpr const_char caseI8Max = arrays[id][36];
        constexpr const_char caseI8Maxa = arrays[id][37];
        constexpr const_char caseI8Min = arrays[id][38];
        constexpr const_char caseI8Mina = arrays[id][39];


        constexpr const_char caseU64Max = arrays[id][40];
        constexpr const_char caseU64Maxa = arrays[id][41];
        constexpr const_char caseU64Min = arrays[id][42];
        constexpr const_char caseU64Mina = arrays[id][43];

        constexpr const_char caseU32Max = arrays[id][44];
        constexpr const_char caseU32Maxa = arrays[id][45];
        constexpr const_char caseU32Min = arrays[id][46];
        constexpr const_char caseU32Mina = arrays[id][47];

        constexpr const_char caseU16Max = arrays[id][48];
        constexpr const_char caseU16Maxa = arrays[id][49];
        constexpr const_char caseU16Min = arrays[id][50];
        constexpr const_char caseU16Mina = arrays[id][51];

        constexpr const_char caseU8Max = arrays[id][52];
        constexpr const_char caseU8Maxa = arrays[id][53];
        constexpr const_char caseU8Min = arrays[id][54];
        constexpr const_char caseU8Mina = arrays[id][55];

        // Assert test
        static_assert(case1.to_integer<T>(baseMult) == 124); // case 1
        static_assert(case1a.to_integer<T>(baseMult) == 124); // case 1a
        static_assert(case2.to_integer<T>(baseMult) == static_cast<T>(-124)); // case 2
        static_assert(case2a.to_integer<T>(baseMult) == static_cast<T>(-124)); // case 2a
        static_assert(case3.to_integer<T>(baseMult) == static_cast<T>(-124)); // case 3
        static_assert(case3a.to_integer<T>(baseMult) == static_cast<T>(-124)); // case 3a
        static_assert(case4.to_integer<T>(baseMult) == 124); // case 4
        static_assert(case4a.to_integer<T>(baseMult) == 124); // case 4a
        static_assert(case5.to_integer<T>(baseMult) == 124); // case 5
        static_assert(case5a.to_integer<T>(baseMult) == 124); // case 5a
        static_assert(case6.to_integer<T>(baseMult) == static_cast<T>(-124)); // case 6
        static_assert(case6a.to_integer<T>(baseMult) == static_cast<T>(-124)); // case 6a
        static_assert(case7.to_integer<T>(baseMult) == 22); // case 7
        static_assert(case7a.to_integer<T>(baseMult) == 22); // case 7a
        static_assert(case8.to_integer<T>(baseMult) == static_cast<T>(-22)); // case 8
        static_assert(case8a.to_integer<T>(baseMult) == static_cast<T>(-22)); // case 8a
        static_assert(case9.to_integer<T>(baseMult) == 0); // case 9
        static_assert(case9a.to_integer<T>(baseMult) == 0); // case 9a
        static_assert(case10.to_integer<T>(baseMult) == 0); // case 10
        static_assert(case10a.to_integer<T>(baseMult) == 0); // case 10a
        static_assert(case11.to_integer<T>(baseMult) == 25); // case 11
        static_assert(case11a.to_integer<T>(baseMult) == 25); // case 11a
        static_assert(case12.to_integer<T>(baseMult) == static_cast<T>(-25)); // case 12
        static_assert(case12a.to_integer<T>(baseMult) == static_cast<T>(-25)); // case 12a

        if constexpr (sizeof(T) == 8)
        {
            static_assert(caseI64Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int64_t>::max()));
            static_assert(caseI64Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int64_t>::max()));
            static_assert(caseI64Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int64_t>::min()));
            static_assert(caseI64Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int64_t>::min()));
            if constexpr (std::is_unsigned_v<T>)
            {
                static_assert(caseU64Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint64_t>::max()));
                static_assert(caseU64Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint64_t>::max()));
                static_assert(caseU64Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint64_t>::min()));
                static_assert(caseU64Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint64_t>::min()));
            }

            static_assert(caseI32Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int32_t>::max()));
            static_assert(caseI32Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int32_t>::max()));
            static_assert(caseI32Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int32_t>::min()));
            static_assert(caseI32Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int32_t>::min()));

            static_assert(caseU32Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint32_t>::max()));
            static_assert(caseU32Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint32_t>::max()));
            static_assert(caseU32Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint32_t>::min()));
            static_assert(caseU32Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint32_t>::min()));

            static_assert(caseI16Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::max()));
            static_assert(caseI16Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::max()));
            static_assert(caseI16Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::min()));
            static_assert(caseI16Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::min()));

            static_assert(caseU16Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::max()));
            static_assert(caseU16Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::max()));
            static_assert(caseU16Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::min()));
            static_assert(caseU16Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::min()));

            static_assert(caseI8Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::max()));
            static_assert(caseI8Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::max()));
            static_assert(caseI8Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::min()));
            static_assert(caseI8Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::min()));

            static_assert(caseU8Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::max()));
            static_assert(caseU8Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::max()));
            static_assert(caseU8Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::min()));
            static_assert(caseU8Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::min()));
        }
        else if constexpr (sizeof(T) == 4)
        {
            static_assert(caseI32Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int32_t>::max()));
            static_assert(caseI32Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int32_t>::max()));
            static_assert(caseI32Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int32_t>::min()));
            static_assert(caseI32Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int32_t>::min()));

            if constexpr (std::is_unsigned_v<T>)
            {
                static_assert(caseU32Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint32_t>::max()));
                static_assert(caseU32Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint32_t>::max()));
                static_assert(caseU32Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint32_t>::min()));
                static_assert(caseU32Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint32_t>::min()));
            }

            static_assert(caseI16Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::max()));
            static_assert(caseI16Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::max()));
            static_assert(caseI16Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::min()));
            static_assert(caseI16Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::min()));

            static_assert(caseU16Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::max()));
            static_assert(caseU16Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::max()));
            static_assert(caseU16Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::min()));
            static_assert(caseU16Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::min()));

            static_assert(caseI8Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::max()));
            static_assert(caseI8Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::max()));
            static_assert(caseI8Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::min()));
            static_assert(caseI8Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::min()));

            static_assert(caseU8Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::max()));
            static_assert(caseU8Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::max()));
            static_assert(caseU8Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::min()));
            static_assert(caseU8Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::min()));
        }
        else if constexpr (sizeof(T) == 2)
        {
            static_assert(caseI16Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::max()));
            static_assert(caseI16Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::max()));
            static_assert(caseI16Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::min()));
            static_assert(caseI16Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int16_t>::min()));

            if constexpr (std::is_unsigned_v<T>)
            {
                static_assert(caseU16Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::max()));
                static_assert(caseU16Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::max()));
                static_assert(caseU16Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::min()));
                static_assert(caseU16Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint16_t>::min()));
            }

            static_assert(caseI8Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::max()));
            static_assert(caseI8Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::max()));
            static_assert(caseI8Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::min()));
            static_assert(caseI8Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::min()));

            static_assert(caseU8Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::max()));
            static_assert(caseU8Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::max()));
            static_assert(caseU8Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::min()));
            static_assert(caseU8Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::min()));
        }
        else if constexpr (sizeof(T) == 1)
        {
            static_assert(caseI8Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::max()));
            static_assert(caseI8Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::max()));
            static_assert(caseI8Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::min()));
            static_assert(caseI8Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<int8_t>::min()));
            if constexpr (std::is_unsigned_v<T>)
            {
                static_assert(caseU8Max.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::max()));
                static_assert(caseU8Maxa.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::max()));
                static_assert(caseU8Min.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::min()));
                static_assert(caseU8Mina.to_integer<T>(baseMult) == static_cast<T>(std::numeric_limits<uint8_t>::min()));
            }
        }

    }
}


namespace TESTING{
    void CONST_CHAR_HPP() noexcept
    {
        using namespace babel::CHAR;
        //constexpr test (only static_assert)
        constexpr const char* d1 = "TestConstexpr";  // 13
        constexpr const char* d2 = "VeryLongTextVeryLongTextVeryLongText";  // 36
        constexpr const char* d3 = "1234";  // 4

        constexpr const_char ccEmpty(""); // no
        constexpr const_char def; // no
        constexpr const_char cc1(d1);  // d1
        constexpr const_char cc2(d2);  // d2
        constexpr const_char cc3(d3); // d3
        constexpr const_char cc4(cc3); // d3
        constexpr const_char ccSpace("With space");

        // Test count, size, cast to std::array
        static_assert(def.size() == 0 && def.data() == nullptr);
        static_assert(cc1.size() == 13 && cc1.data() != nullptr);
        static_assert(cc2.size() == 36 && cc2.data() != nullptr);
        static_assert(cc3.size() == 4 && cc3.data() != nullptr);
        static_assert(cc4.size() == 4 && cc4.data() != nullptr && cc4.data() == cc3.data());

        constexpr auto defCount = def.count('a');
        static_assert(defCount == 0);

        constexpr auto cc1Count = cc1.count('a');
        constexpr auto cc1Count2 = cc1.count('e');
        static_assert(cc1Count == 0 && cc1Count2 == 2);

        constexpr auto cc2Count = cc2.count('a');
        constexpr auto cc2Count2 = cc2.count('V');
        static_assert(cc2Count == 0 && cc2Count2 == 3);

        constexpr auto cc3Count = cc3.count('a');
        constexpr auto cc3Count2 = cc3.count('1');
        static_assert(cc3Count == 0 && cc3Count2 == 1);

        constexpr auto cc4Count = cc4.count('a');
        constexpr auto cc4Count2 = cc4.count('1');
        static_assert(cc4Count == 0 && cc4Count2 == 1);

        static_assert(cc4 == cc3);
        static_assert(!(cc4 != cc3));
        static_assert(cc4 != cc2 && cc2 != def);
        static_assert(cc4.count_if([](const char a_Char)
                                   {
                                       return (static_cast<int>(a_Char - '0') % 2) == 0;
                                   }));

        constexpr auto countIf = cc1.count_if([](const char a_Char)
                                              {
                                                  return a_Char == 'T' || a_Char == 't';
                                              });
        static_assert(countIf == 3);

        constexpr auto cc3Array = cc3.to_array<cc3.size()>();
        static_assert(cc3Array.size() == cc3.size() + 1u /* +1 because array have '\0' on last element*/);
        static_assert(cc3Array[0] == cc3[0]);
        static_assert(cc3Array[1] == cc3[1]);
        static_assert(cc3Array[2] == cc3.at(2));
        static_assert(cc3Array[3] == cc3.at(3));

        constexpr const_char cc5("String create in argument!");
        static_assert(cc5.size() == 26);
        static_assert(cc5.count('!') == 1);
        static_assert(cc5.count('a') == 2);

        // Test valid and empty

        constexpr auto cc3IsValid = cc3.is_valid();
        constexpr auto defIsValid = def.is_valid();
        static_assert(cc3IsValid && !defIsValid);
        static_assert(ccEmpty.is_empty() && def.is_empty() && !cc3.is_empty());

        // Test find

        constexpr auto cc3Found1 = cc3.find('3');
        constexpr auto cc3Found2 = cc3.find('9');
        constexpr auto defFound = cc3.find('A');
        static_assert(cc3Found1 && !cc3Found2 && !defFound);
        constexpr auto cc3FoundIf1 = cc3.find_if([](const char D)
                                                 {
                                                     return static_cast<int>(D-'0') % 2 == 0;
                                                 });

        constexpr auto cc3FoundIf2 = cc3.find_if([](const char D)
                                                 {
                                                     return static_cast<int>(D-'0') >= 5;
                                                 });

        static_assert(cc3FoundIf1 && !cc3FoundIf2);

        // Test conaints
        static_assert(cc3.contains("1234"));
        static_assert(!cc3.contains("12345"));
        static_assert(cc3.contains("4"));
        static_assert(!cc3.contains("45"));

        static_assert(!def.contains("45"));
        static_assert(!def.contains("a"));
        static_assert(def.contains(""));

        static_assert(ccEmpty.contains(""));
        static_assert(!ccEmpty.contains("a"));

        static_assert(ccSpace.contains(""));
        static_assert(ccSpace.contains(" "));
        static_assert(ccSpace.contains(" space"));
        static_assert(ccSpace.contains("space"));
        static_assert(ccSpace.contains("With space"));
        static_assert(!ccSpace.contains("with space"));
        static_assert(!ccSpace.contains("With spaced"));





        // ==== Test Decimal ===
        // Test with signed value
        integer_test<int64_t, BASE::DEC>();
        integer_test<int32_t, BASE::DEC>();
        integer_test<int16_t, BASE::DEC>();
        integer_test<int8_t, BASE::DEC>();

        // Test with unsigned value
        integer_test<uint64_t, BASE::DEC>();
        integer_test<uint32_t, BASE::DEC>();
        integer_test<uint16_t, BASE::DEC>();
        integer_test<uint8_t, BASE::DEC>();

        // ==== Test HEX ===
        // Test with signed value
        integer_test<int64_t, BASE::HEX>();
        integer_test<int32_t, BASE::HEX>();
        integer_test<int16_t, BASE::HEX>();
        integer_test<int8_t, BASE::HEX>();

        // Test with unsigned value
        integer_test<uint64_t, BASE::HEX>();
        integer_test<uint32_t, BASE::HEX>();
        integer_test<uint16_t, BASE::HEX>();
        integer_test<uint8_t, BASE::HEX>();

        // ==== Test OCTAL ===
        // Test with signed value
        integer_test<int64_t, BASE::OCT>();
        integer_test<int32_t, BASE::OCT>();
        integer_test<int16_t, BASE::OCT>();
        integer_test<int8_t, BASE::OCT>();

        // Test with unsigned value
        integer_test<uint64_t, BASE::OCT>();
        integer_test<uint32_t, BASE::OCT>();
        integer_test<uint16_t, BASE::OCT>();
        integer_test<uint8_t, BASE::OCT>();

        // ==== Test BIN ===
        // Test with signed value
        integer_test<int64_t, BASE::BIN>();
        integer_test<int32_t, BASE::BIN>();
        integer_test<int16_t, BASE::BIN>();
        integer_test<int8_t, BASE::BIN>();

        // Test with unsigned value
        integer_test<uint64_t, BASE::BIN>();
        integer_test<uint32_t, BASE::BIN>();
        integer_test<uint16_t, BASE::BIN>();
        integer_test<uint8_t, BASE::BIN>();

        // Test iterator
        constexpr bool Iterator_test = test_iterator();
        static_assert(Iterator_test);

        // runtime test (only assert)
        // TODO
    }
} // namespace TESTING
#endif
