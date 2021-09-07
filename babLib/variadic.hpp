// Copyright [2021] <Wojtek>"
#ifndef BABLIB_VARIADIC_HPP_
#define BABLIB_VARIADIC_HPP_

#include <array>
#include <any>
#include "concepts/concepts.hpp"

namespace babel::VARIADIC{

    template< typename Type, typename ... Hold>
    class holder
    {
        static constexpr std::size_t m_size = 1u + sizeof...(Hold);
        // TODO remove std::any i dont have idea now (i dont want to use std::tuple)
        std::array<std::any, m_size> m_hold;

        template<std::size_t I, typename U>
        constexpr void _put(U &&_a1) noexcept
        {
            m_hold[I] = std::forward<U>(_a1);
        }

        template<std::size_t I, typename U, typename ... Args >
        constexpr void _put(U &&_a1, Args &&...args) noexcept
        {
            _put<I + 1>(std::forward<U>(_a1));
            if constexpr (sizeof...(Args) == 1)
            {
                _put<I + 2>(std::forward<Args>(args)...);
            }
            else
            {
                _put<I + 1>(std::forward<Args>(args)...);
            }
        }

        template <std::size_t I, typename T, typename ...Ts>
        struct nth_element_impl {
            using type = typename nth_element_impl<I-1, Ts...>::type;
        };

        template <std::size_t I, typename ...Ts>
        using nth_element = typename nth_element_impl<I, Ts...>::type;

        template <typename T, typename ...Ts>
        struct nth_element_impl<0, T, Ts...> {
            using type = T;
        };
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
            _put<0>(std::forward<T>(arg));
        }

        template< typename T = Type>
        requires ( !std::is_same_v<std::decay_t<Type>, std::decay_t<holder>> && m_size > 1 )
        constexpr explicit holder(T &&arg, Hold &&... args) noexcept
        {
            _put<0>(std::forward<T>(arg));
            _put<0>(std::forward<Hold>(args)...);
        }

        constexpr holder &operator=(const holder &other) noexcept
        {
            m_hold = other.m_hold;
            return *this;
        }

        template<std::size_t I>
        [[nodiscard]] constexpr auto &get() noexcept
        {
            return std::any_cast<nth_element<I, Type, Hold...>&>(m_hold[I]);
        }

        template<std::size_t I>
        [[nodiscard]] constexpr auto &get() const noexcept
        {
            return std::any_cast<const nth_element<I, Type, Hold...>&>(m_hold[I]);
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
