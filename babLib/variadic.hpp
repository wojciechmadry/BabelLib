// Copyright [2021] <Wojtek>"
#ifndef BABLIB_VARIADIC_HPP_
#define BABLIB_VARIADIC_HPP_

#include <array>
#include <any>
#include "concepts/concepts.hpp"

namespace babel::VARIADIC{

    template<std::size_t BaseCounter, typename T>
    class _holderleaf
    {
    public:
        T value;
    };
    template<std::size_t BaseCounter, typename... Hold>
    class _holder;

    template<std::size_t BaseCounter>
    class _holder<BaseCounter>{};

    template<std::size_t BaseCounter, typename Type, typename ... Hold>
    class _holder<BaseCounter, Type, Hold...>: public _holderleaf<BaseCounter, Type>, public _holder<BaseCounter + 1, Hold...>
    {
        static constexpr std::size_t m_size = 1u + sizeof...(Hold);

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


        template<std::size_t I, typename T>
        constexpr void put(T&& arg1) noexcept
        {
            get<I>() = std::forward<T>(arg1);
        }

        template<std::size_t I, typename T, typename ... HOLD>
        constexpr void put(T&& arg1, HOLD&&... Holders) noexcept
        {
            put<I>(std::forward<T>(arg1));
            put<I+1>(std::forward<HOLD>(Holders)...);
        }
    public:
        constexpr _holder() = default;

        template< typename T = Type >
        requires ( !std::is_same_v<std::decay_t<T>, std::decay_t<_holder>> )
        constexpr explicit _holder(T &&arg) noexcept //NOLINT
        {
            put<0>(std::forward<T>(arg));
        }

        template< typename T = Type>
        requires ( !std::is_same_v<std::decay_t<Type>, std::decay_t<_holder>> && m_size > 1 )
        constexpr explicit _holder(T &&arg, Hold &&... args) noexcept
        {
            put<0>(std::forward<T>(arg));
            put<1>(std::forward<Hold>(args)...);
        }

        template<std::size_t I>
        [[nodiscard]] constexpr auto& get() noexcept
        {
            return this->_holderleaf<I, typename nth_element_impl<I, Type, Hold...>::type>::value;
        }

        template<std::size_t I>
        [[nodiscard]] constexpr auto& get() const noexcept
        {
            return this->_holderleaf<I, typename nth_element_impl<I, Type, Hold...>::type>::value;
        }

    };

    template<typename... Items>
    using holder = _holder<0, Items...>;
}  // namespace babel::VARIADIC

#endif  // BABLIB_VARIADIC_HPP_
