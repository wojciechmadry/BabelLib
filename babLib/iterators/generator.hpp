// Copyright [2021] <Wojtek>"
#ifndef BABLIB_ITERATORS_GENERATOR_HPP_
#define BABLIB_ITERATORS_GENERATOR_HPP_

#include <cstdint>
#include <utility>

namespace babel::ITERATOR{

    template< typename Type >
    class generator
    {
        Type m_gen;

        class iterator
        {
            Type *m_gen {nullptr};
            int64_t m_times {0};

        public:
            constexpr iterator(const Type &Sequence, const int64_t Times) noexcept: m_gen(&Sequence), m_times(Times)
            { }

            constexpr iterator(Type *Sequence, const int64_t Times) noexcept: m_gen(Sequence), m_times(Times)
            { }

            [[nodiscard]] constexpr int64_t &times() noexcept
            {
                return m_times;
            }

            [[nodiscard]] constexpr int64_t times() const noexcept
            {
                return m_times;
            }

            constexpr const Type &operator*() const noexcept
            {
                return *m_gen;
            }


            constexpr iterator &operator++()
            {
                --m_times;
                return *this;
            }

            constexpr const iterator operator++(int) //NOLINT
            {
                iterator other(m_gen, m_times);
                --m_times;
                return other;
            }

            constexpr iterator &operator--()
            {
                ++m_times;
                return *this;
            }

            constexpr const iterator operator--(int) //NOLINT
            {
                iterator other(m_gen, m_times);
                ++m_times;
                return other;
            }

            constexpr bool operator==(const iterator &other) const noexcept
            {
                return m_times == other.m_times;
            }

            constexpr bool operator!=(const iterator &other) const noexcept
            {
                return m_times != other.m_times;
            }
        };

    public:
        constexpr generator() = delete;

        constexpr explicit generator(const Type &Sequence) noexcept: m_gen(Sequence)
        { }

        constexpr generator(const generator &Other) noexcept: m_gen(Other.m_gen)
        { }

        constexpr generator(generator &&Other) noexcept: m_gen(std::move(Other.m_gen))
        { }

        [[nodiscard]] Type& stored() noexcept
        {
            return m_gen;
        }

        [[nodiscard]] const Type& stored() const noexcept
        {
            return m_gen;
        }

        [[nodiscard]] constexpr auto begin(const int64_t Times) noexcept
        {
            return iterator(&m_gen, Times);
        }

        [[nodiscard]] constexpr auto end() noexcept
        {
            return iterator(&m_gen, 0);
        }
    };

}  // namespace babel::ITERATOR


#endif  // BABLIB_ITERATORS_GENERATOR_HPP_
