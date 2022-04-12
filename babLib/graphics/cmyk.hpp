// Copyright [2021] <Wojtek>"
#ifndef BABLIB_GRAPHICS_CMYK_HPP_
#define BABLIB_GRAPHICS_CMYK_HPP_

#include "../algorithm/algorithm.hpp"

namespace babel::GRAPHICS{
    //------------------CMYK---------------
    class cmyk
    {
    public:
        using byte = uint8_t;
    private:
        std::array<byte, 4> m_CMYK;

        [[nodiscard]] static constexpr byte max(const byte Value) noexcept
        {
            return Value > 100 ? static_cast<byte>(100) : Value;
        }

        constexpr void check_and_fix() noexcept
        {
            m_CMYK[0] = this->max(m_CMYK[0]);
            m_CMYK[1] = this->max(m_CMYK[1]);
            m_CMYK[2] = this->max(m_CMYK[2]);
            m_CMYK[3] = this->max(m_CMYK[3]);
        }

        constexpr void set_at(const byte index, const byte Value) noexcept
        {
            m_CMYK[index] = this->max(Value);
        }

    public:
        constexpr explicit cmyk(const byte C = 0, const byte M = 0, const byte Y = 0, //NOLINT
                                const byte K = 0) noexcept //NOLINT
        {
            set(C, M, Y, K);
        }

        constexpr cmyk(const cmyk &other) noexcept = default;


        [[nodiscard]] constexpr const std::array<byte, 4> &get_array() const noexcept
        {
            return m_CMYK;
        }

        [[nodiscard]] constexpr byte C() const noexcept
        {
            return m_CMYK[0];
        }

        [[nodiscard]] constexpr byte M() const noexcept
        {
            return m_CMYK[1];
        }

        [[nodiscard]] constexpr byte Y() const noexcept
        {
            return m_CMYK[2];
        }

        [[nodiscard]] constexpr byte K() const noexcept
        {
            return m_CMYK[3];
        }


        [[nodiscard]] constexpr byte operator[](const byte index) const
        {
            if ( index > 3 )
                throw std::out_of_range("Array out of range.");
            return m_CMYK[index];
        }

        constexpr void set(const byte C, const byte M, const byte Y, const byte K) noexcept
        {
            m_CMYK[0] = this->max(C);
            m_CMYK[1] = this->max(M);
            m_CMYK[2] = this->max(Y);
            m_CMYK[3] = this->max(K);
        }


        constexpr void set_C(const byte C) noexcept
        {
            set_at(0, C);
        }

        constexpr void set_M(const byte M) noexcept
        {
            set_at(1, M);
        }


        constexpr void set_Y(const byte Y) noexcept
        {
            set_at(2, Y);
        }

        constexpr void set_K(const byte K) noexcept
        {
            set_at(3, K);
        }
    };


}  // namespace babel::GRAPHICS

#endif  // BABLIB_GRAPHICS_CMYK_HPP_
