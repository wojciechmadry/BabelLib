// Copyright [2021] <Wojtek>"
#ifndef BABLIB_CONST_CHAR_HPP_
#define BABLIB_CONST_CHAR_HPP_

namespace babel::CHAR{

    class const_char
    {
        const char *m_data;
        std::size_t m_size;

        [[nodiscard]] static constexpr char to_upp(char a_Char) noexcept
        {
            if ( a_Char >= 'a' && a_Char <= 'z' )
            {
                a_Char = static_cast<char>(a_Char - ( 'a' - 'A' ));
            }
            return a_Char;
        }

        [[nodiscard]] static constexpr std::size_t len(const char *a_Data) noexcept
        {
            std::size_t u64Len = 0u;
            if ( a_Data != nullptr )
            {
                while ( *a_Data != '\0' )
                {
                    ++a_Data;
                    ++u64Len;
                }
            }
            return u64Len;
        }

        template< typename T >
        [[nodiscard]] constexpr T number(char a_Char) const noexcept
        {
            T result = 0;
            if ( a_Char >= '0' && a_Char <= '9' )
            {
                result = static_cast<T>(a_Char - '0');
            } else if ( a_Char = to_upp(a_Char); a_Char >= 'A' && a_Char <= 'F' )
            {
                result = static_cast<T>(a_Char - 'A') + 10;
            }
            return result;
        }

        [[nodiscard]] constexpr bool contains(const char *a_Data, const std::size_t a_Size) const noexcept
        {
            if ( a_Size > m_size )
            {
                return false;
            } else if ( a_Size == m_size && a_Size == 0 )
            {
                return true;
            }

            for ( std::size_t i = 0 ; i < m_size ; ++i )
            {
                std::size_t temp_i = i;
                std::size_t foundLen = 0u;

                for ( std::size_t j = 0 ; j < a_Size && temp_i < m_size ; ++j, ++temp_i )
                {
                    if ( a_Data[j] == m_data[temp_i] )
                    {
                        ++foundLen;
                    } else
                    {
                        break;
                    }
                }

                if ( foundLen == a_Size )
                {
                    return true;
                }
            }
            return false;
        }

    public:

        constexpr const_char() noexcept
                : m_data(nullptr), m_size(0u)
        {
        }

        explicit constexpr const_char(const char *a_Data) noexcept
                : m_data(a_Data), m_size(len(a_Data))
        {
        }

        constexpr const_char(const_char &&a_Other) noexcept
                : m_data(a_Other.m_data), m_size(a_Other.m_size)
        {
        }

        constexpr const_char(const const_char &a_Other) noexcept = default;

        explicit const_char(const std::string &a_String) noexcept
                : m_data(a_String.data()), m_size(a_String.size())
        {
        }

        constexpr const_char &operator=(const const_char &a_Other) noexcept
        {
            if ( this == &a_Other )
            {
                return *this;
            }
            m_data = a_Other.m_data;
            m_size = a_Other.m_size;
            return *this;
        }

        constexpr const_char &operator=(const_char &&a_Other) noexcept
        {
            m_data = a_Other.m_data;
            m_size = a_Other.m_size;
            return *this;
        }

        constexpr const_char &operator=(const char *a_Data) noexcept
        {
            m_data = a_Data;
            m_size = len(m_data);
            return *this;
        }

        const_char &operator=(const std::string &a_String) noexcept
        {
            m_data = a_String.data();
            m_size = a_String.size();
            return *this;
        }

        [[nodiscard]] constexpr std::size_t size() const noexcept
        {
            return m_size;
        }

        [[nodiscard]] constexpr const char *data() const noexcept
        {
            return m_data;
        }

        [[nodiscard]] constexpr std::size_t count(const char a_Char) const noexcept
        {
            return static_cast<std::size_t>(std::count(m_data, m_data + m_size, a_Char));
        }

        template< typename Func >
        [[nodiscard]] constexpr std::size_t count_if(Func a_function) const noexcept
        {
            return static_cast<std::size_t>(std::count_if(m_data, m_data + m_size, a_function));
        }

        template< std::size_t SIZE >
        [[nodiscard]] constexpr auto to_array() const noexcept
        {
            std::array<char, SIZE + 1u> result;
            std::copy(m_data, m_data + m_size, std::begin(result));
            result[SIZE] = '\0';
            return result;
        }

        [[nodiscard]] auto to_vector() const noexcept
        {
            std::vector<char> result(m_size + 1);
            std::copy(m_data, m_data + m_size, std::begin(result));
            result[m_size] = '\0';
            return result;
        }

        [[nodiscard]] std::string to_string() const noexcept
        {
            return std::string {m_data};
        }

        [[nodiscard]] constexpr bool operator==(const const_char &a_Other) const noexcept
        {
            if ( m_size != a_Other.m_size )
            {
                return false;
            }
            for ( std::size_t i = 0 ; i < m_size ; ++i )
            {
                if ( m_data[i] != a_Other.m_data[i] )
                {
                    return false;
                }
            }
            return true;
        }

        [[nodiscard]] constexpr bool operator!=(const const_char &a_Other) const noexcept
        {
            return !( *this == a_Other );
        }

        [[nodiscard]] constexpr char operator[](const std::size_t a_Index) const noexcept
        {
            if ( a_Index < m_size )
            {
                return m_data[a_Index];
            }
            return '\0';
        }

        [[nodiscard]] constexpr char at(const std::size_t a_Index) const noexcept
        {
            return this->operator[](a_Index);
        }

        [[nodiscard]] constexpr bool is_valid() const noexcept
        {
            return m_data != nullptr;
        }

        [[nodiscard]] constexpr bool is_empty() const noexcept
        {
            return m_size == 0;
        }

        [[nodiscard]] constexpr bool find(const char a_Char) const noexcept
        {
            auto found = std::find(m_data, m_data + m_size, a_Char);
            return found != m_data + m_size;
        }

        template< typename Func >
        [[nodiscard]] constexpr bool find_if(Func function) const noexcept
        {
            auto found = std::find_if(m_data, m_data + m_size, function);
            return found != m_data + m_size;
        }

        [[nodiscard]] constexpr bool contains(const char *a_Data) const noexcept
        {
            return contains(a_Data, len(a_Data));
        }

        [[nodiscard]] bool contains(const std::string &a_String) const noexcept
        {
            return contains(a_String.data(), a_String.size());
        }

        [[nodiscard]] constexpr bool contains(const const_char &a_Data) const noexcept
        {
            return contains(a_Data.data(), a_Data.size());
        }

        [[nodiscard]] constexpr int64_t to_int64(const int64_t a_base = 10) const
        {
            if ( a_base != 2 && a_base != 8 && a_base != 10 && a_base != 16 )
            {
                throw std::invalid_argument("to_int64: Bad base {2, 8, 10, 16}");
            }

            if ( m_size == 0 )
            {
                throw std::invalid_argument("to_int64");
            }

            const char *start_range = m_data;
            bool result_is_minus = false;
            if ( *start_range == '-' )
            {
                result_is_minus = true;
                ++start_range;
            }

            if ( a_base == 16 )
            {
                if ( *start_range != '\0' && *( start_range + 1 ) != '\0' )
                {
                    char X_char = to_upp(*( start_range + 1 ));
                    if ( *start_range == '0' && X_char == 'X' )
                    {
                        start_range += 2;
                    }
                }
            }

            std::size_t acces_range = 0u;
            const char *search_ptr = start_range;
            while ( *search_ptr != '\0' )
            {
                if ( *search_ptr >= '0' && *search_ptr <= '9' )
                {
                    ++search_ptr;
                    ++acces_range;
                } else if ( char Upper = to_upp(*search_ptr); Upper >= 'A' && Upper <= 'F' )
                {
                    if ( a_base != 16 )
                    {
                        break;
                    }
                    ++search_ptr;
                    ++acces_range;
                } else
                {
                    break;
                }
            }
            if ( acces_range == 0u )
            {
                throw std::invalid_argument("to_int64");
            }

            int64_t result = 0;

            if ( result_is_minus )
            {
                std::for_each(start_range, start_range + acces_range,
                              [&](char a_Char) {
                                  result = result * a_base - number<int64_t>(a_Char);
                              });
            } else
            {
                std::for_each(start_range, start_range + acces_range,
                              [&](char a_Char) {
                                  result = result * a_base + number<int64_t>(a_Char);
                              });
            }

            if ( result < 0 && !result_is_minus )
            {
                throw std::out_of_range("to_int64");
            }
            if ( result > 0 && result_is_minus )
            {
                throw std::out_of_range("to_int64");
            }
            return result;
        }
    };

}

#endif  //  BABLIB_CONST_CHAR_HPP_