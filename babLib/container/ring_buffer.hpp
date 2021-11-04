// Copyright [2021] <Wojtek>"
#ifndef BABLIB_RING_BUFFER_HPP_
#define BABLIB_RING_BUFFER_HPP_

#include <array>
#include <concepts>
#include <stdexcept>
#include <type_traits>

namespace babel::CONTAINER{

    template< typename T, std::size_t SIZE, bool SAFE_MODE = true >
    requires(std::is_default_constructible_v<std::decay_t<T>>)
    class RingBuffer
    {
        static_assert(SIZE > 0, "Size must be greater than 0");

        struct ValidData
        {
            bool isValid;
            T data;

            ValidData() noexcept = default;

            ValidData(const bool a_isValid, T &&a_data) noexcept
                    : isValid(a_isValid), data(std::move(a_data))
            {

            }
        };

    public:

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using lValue = T &&;
        using iterator = typename std::array<T, SIZE>::iterator;
        using const_iterator = typename std::array<T, SIZE>::iterator;
        using size_type = std::decay_t<decltype(SIZE)>;
        using pointer = T *;
        using const_pointer = const T *;
        using read_type = ValidData;
    private:

        struct rb_write
        {
        };
        struct rb_read
        {
        };

        std::array<value_type, SIZE> m_buffer;
        iterator m_reader = std::begin(m_buffer);
        iterator m_writer = std::begin(m_buffer);
        size_type m_size = 0;

        void check_iterator(iterator &a_Iterator) noexcept
        {
            if ( a_Iterator == std::end(m_buffer) )
            {
                a_Iterator = std::begin(m_buffer);
            }
        }

        template< typename Operation >
        requires ( std::is_same_v<rb_write, Operation> || std::is_same_v<rb_read, Operation> )
        [[nodiscard]] bool check_exception() noexcept
        {
            if constexpr ( std::is_same_v<rb_write, Operation> )
            {
                if ( m_size == SIZE )
                {
                    return true;
                }
                ++m_size;
            } else if constexpr ( std::is_same_v<rb_read, Operation> )
            {
                if ( m_size == 0 )
                {
                    return true;
                }
                --m_size;
            }
            return false;
        }

        template< typename U=value_type >
        requires(std::is_convertible_v<std::decay_t<U>, value_type>)
        bool write(U
        && a_Data) noexcept
        {
            auto Exception = check_exception<rb_write>();
            if constexpr ( SAFE_MODE )
            {
                if ( !Exception )
                {
                    check_iterator(m_writer);
                    *m_writer = std::forward<U>(a_Data);
                    ++m_writer;
                }
            } else
            {
                check_iterator(m_writer);
                *m_writer = std::forward<U>(a_Data);
                ++m_writer;
            }


            return Exception;
        }

        [[nodiscard]] read_type read() noexcept
        {
            auto Exception = check_exception<rb_read>();
            if ( !Exception )
            {
                check_iterator(m_reader);
                auto TemporaryData = std::move(*m_reader);
                ++m_reader;
                return {true, std::move(TemporaryData)};
            }
            return {false, { }};
        }

    public:
        RingBuffer() noexcept = default;

        ~RingBuffer() noexcept = default;

        bool write_data(const_reference a_Data) noexcept
        {
            return write(a_Data);
        }

        [[nodiscard]] read_type read_data() noexcept
        {
            return read();
        }

        [[nodiscard]] size_type size() const noexcept
        {
            return m_size;
        }

        [[nodiscard]] consteval size_type capacity() const noexcept
        {
            return SIZE;
        }

        [[nodiscard]] consteval bool is_safe_mode() const noexcept
        {
            return SAFE_MODE;
        }

        void clear() noexcept
        {
            m_reader = std::begin(m_buffer);
            m_writer = std::begin(m_buffer);
            m_size = 0;
        }

    };

}  // namespace babel::CONTAINER
#endif  // BABLIB_RING_BUFFER_HPP_
