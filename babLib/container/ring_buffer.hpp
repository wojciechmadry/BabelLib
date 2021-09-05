// Copyright [2021] <Wojtek>"
#ifndef BABLIB_RING_BUFFER_HPP_
#define BABLIB_RING_BUFFER_HPP_

#include <array>
#include <concepts>
#include <stdexcept>
#include <type_traits>

namespace babel::CONTAINER{
    
    template< typename T, std::size_t SIZE >
    class RingBuffer
    {
        static_assert(SIZE > 0, "Size must be greater than 0");

    public:

        class read_exception : public std::exception
        {
        public:
            virtual const char *what() const noexcept override
            {
                return "...";
            }
        };

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using lValue = T &&;
        using iterator = typename std::array<T, SIZE>::iterator;
        using const_iterator = typename std::array<T, SIZE>::iterator;
        using size_type = std::decay_t<decltype(SIZE)>;
        using safe_type = typename std::make_signed<size_type>::type;
        using pointer = T *;
        using const_pointer = const T *;

    private:

        std::array<value_type, SIZE> m_buffer;
        iterator m_reader = std::begin(m_buffer);
        iterator m_writer = std::begin(m_buffer);
        safe_type m_safe_counter = 0;

        void check_iterator(iterator &a_Iterator) noexcept
        {
            if ( a_Iterator == std::end(m_buffer) )
            {
                a_Iterator = std::begin(m_buffer);
            }
        }

        template< typename U=value_type >
        requires(std::is_convertible_v<std::decay_t<U>, value_type>)
        void write(U
        && a_Data)
        {
            // TODO Exceptions
            check_iterator(m_writer);
            *m_writer = std::forward<U>(a_Data);
            ++m_writer;
            ++m_safe_counter;
        }

        value_type read()
        {
            // TODO Exceptions
            check_iterator(m_reader);
            auto TemporaryData = std::move(*m_reader);
            ++m_reader;
            --m_safe_counter;
            return std::move(TemporaryData);
        }

    public:

        void write_data(const_reference a_Data)
        {
            write(a_Data);
        }

        value_type read_data()
        {
            return read();
        }

        size_type size() const noexcept
        {
            return SIZE;
        }

    };

}  // namespace babel::CONTAINER
#endif  // BABLIB_RING_BUFFER_HPP_
