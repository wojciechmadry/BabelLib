// Copyright [2021] <Wojtek>"
#ifndef BABLIB_VARIADIC_HPP_
#define BABLIB_VARIADIC_HPP_

#include <array>
#include <any>
#include "concepts/concepts.hpp"

namespace babel::VARIADIC{
    template< typename Type, typename ... Hold>
    requires(babel::CONCEPTS::IS_NOT_ANY_VOID<Type>)
    class holder
    {
        static constexpr std::size_t m_size = 1u + sizeof...(Hold);
        std::array<std::any, m_size> m_hold;
        typename std::array<std::any, m_size>::iterator m_iterator = std::begin(m_hold);

        template< typename U = Type >
        requires(std::is_same_v<std::decay_t<U>, std::decay_t<Type>>)
        constexpr void _put(U &&_a1) noexcept
        {
            *m_iterator = std::forward<U>(_a1);
            ++m_iterator;
        }

        template< typename U = Type, typename ... Args >
        requires(std::is_same_v<std::decay_t<U>, std::decay_t<Type>>)
        constexpr void _put(U &&_a1, Args &&...args) noexcept
        {
            _put(std::forward<U>(_a1));
            _put(std::forward<Args>(args)...);
        }

    public:
        using Container = std::decay_t<decltype(m_hold)>;

        constexpr holder() = default;

        constexpr holder(const holder &other) noexcept
        {
            m_hold = other.m_hold;
        }

        template< typename T = Type >
        requires ( !std::is_same_v<std::decay_t<T>, std::decay_t<holder>> )
        constexpr explicit holder(T &&arg) noexcept //NOLINT
        {
            _put(std::forward<T>(arg));
        }

        template< typename T = Type>
        requires ( !std::is_same_v<std::decay_t<Type>, std::decay_t<holder>> && m_size > 1 )
        constexpr explicit holder(T &&arg, Hold &&... args) noexcept
        {
            _put(std::forward<T>(arg));
            _put(std::forward<Hold>(args)...);
        }

        constexpr holder &operator=(const holder &other) noexcept
        {
            m_hold = other.m_hold;
            return *this;
        }

        [[nodiscard]] constexpr Type &operator[](const std::size_t index)
        {
            return m_hold[index];
        }

        [[nodiscard]] constexpr const Type &operator[](const std::size_t index) const
        {
            return m_hold[index];
        }

        [[nodiscard]] constexpr auto operator->()
        {
            return &m_hold;
        }

        [[nodiscard]] constexpr auto operator->() const
        {
            return &m_hold;
        }

        /**
         *  @brief  Return vector of storage parameter
         *  @return Return vector&
         */
        [[nodiscard]] constexpr Container &get() noexcept
        {
            return m_hold;
        }

        /**
         *  @brief  Return vector of storage parameter
         *  @return Return const vector&
         */
        [[nodiscard]] constexpr const Container &get() const noexcept
        {
            return m_hold;
        }
    };
}  // namespace babel::VARIADIC

#endif  // BABLIB_VARIADIC_HPP_
