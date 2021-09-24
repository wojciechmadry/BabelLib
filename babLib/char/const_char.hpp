// Copyright [2021] <Wojtek>"
#ifndef BABLIB_CONST_CHAR_HPP_
#define BABLIB_CONST_CHAR_HPP_

namespace babel::CHAR{
    class const_char
    {
        const char* m_data;
        std::size_t m_size;

        [[nodiscard]] static constexpr std::size_t len(const char* a_Data) noexcept
        {
            std::size_t u64Len = 0u;
            if (a_Data != nullptr)
            {
                while(*a_Data != '\0')
                {
                    ++a_Data;
                    ++u64Len;
                }
            }
            return u64Len;
        }

    public:

        constexpr const_char() noexcept
                : m_data(nullptr), m_size(0u)
        {

        }

        explicit constexpr const_char(const char* a_Data) noexcept
                : m_data (a_Data), m_size(len(a_Data))
        {

        }

        constexpr const_char(const_char&& a_Other) noexcept
                : m_data (a_Other.m_data), m_size(a_Other.m_size)
        {

        }

        constexpr const_char(const const_char& a_Other) noexcept = default;

        explicit const_char(const std::string& a_String) noexcept
                : m_data (a_String.data()), m_size(a_String.size())
        {

        }

        constexpr const_char& operator=(const const_char& a_Other) noexcept
        {
            if (this == &a_Other)
            {
                return *this;
            }
            m_data = a_Other.m_data;
            m_size = a_Other.m_size;
            return *this;
        }

        constexpr const_char& operator=(const_char&& a_Other) noexcept
        {
            m_data = a_Other.m_data;
            m_size = a_Other.m_size;
            return *this;
        }

        constexpr const_char& operator=(const char* a_Data) noexcept
        {
            m_data = a_Data;
            m_size = len(m_data);
            return *this;
        }

        const_char& operator=(const std::string& a_String) noexcept
        {
            m_data = a_String.data();
            m_size = a_String.size();
            return *this;
        }

        [[nodiscard]] constexpr std::size_t size() const noexcept
        {
            return m_size;
        }

        [[nodiscard]] constexpr const char* data() const noexcept
        {
            return m_data;
        }

        [[nodiscard]] constexpr std::size_t count(const char a_Char) const noexcept
        {
            return static_cast<std::size_t>(std::count(m_data, m_data + m_size, a_Char));
        }

        template<typename Func>
        [[nodiscard]] constexpr std::size_t count_if(Func a_function) const noexcept
        {
            return static_cast<std::size_t>(std::count_if(m_data, m_data + m_size , a_function));
        }

        template<std::size_t SIZE>
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
            return std::string{m_data};
        }

        [[nodiscard]] constexpr bool operator==(const const_char& a_Other) const noexcept
        {
            if (m_size != a_Other.m_size)
            {
                return false;
            }

            for(std::size_t i = 0 ; i < m_size ; ++i)
            {
                if (m_data[i] != a_Other.m_data[i])
                {
                    return false;
                }
            }

            return true;
        }

        [[nodiscard]] constexpr bool operator!=(const const_char& a_Other) const noexcept
        {
            return !(*this == a_Other);
        }

        [[nodiscard]] constexpr char operator[](const std::size_t a_Index) const noexcept
        {
            if (a_Index < m_size)
            {
                return m_data[a_Index];
            }
            return '\0';
        }

        [[nodiscard]] constexpr char at(const std::size_t a_Index) const noexcept
        {
            return this->operator[](a_Index);
        }
    };

}

#endif  //  BABLIB_CONST_CHAR_HPP_