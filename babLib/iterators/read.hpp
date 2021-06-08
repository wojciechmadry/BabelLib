#ifndef babel_ITERATOR_READ
#define babel_ITERATOR_READ

#include "../must_have.hpp"

namespace babel::ITERATOR{

    class reader
    {
        bool _end_line {true};
        std::ifstream *_if {nullptr};
        std::string _line;

        class Iterator
        {
            bool _end_line {true};
            std::ifstream *_if {nullptr};
            std::string _line;
        public:
            Iterator() = default;

            Iterator(std::ifstream *If, const bool _end) : _end_line(_end), _if(If)
            { }

            ~Iterator() = default;

            [[nodiscard]] const std::string &operator*() const noexcept
            {
                return _line;
            }

            [[nodiscard]] std::string &operator*() noexcept
            {
                return _line;
            }

            Iterator &operator++() noexcept
            {
                _end_line = static_cast<bool>(std::getline(*_if, _line));
                return *this;
            }

            bool operator==(const Iterator &other) const noexcept
            {
                return _end_line == other._end_line;
            }

            bool operator!=(const Iterator &other) const noexcept
            {
                return _end_line != other._end_line;
            }
        };

    public:
        reader() = default;

        reader(const reader &) = default;

        reader(reader &&Reader) noexcept
        {
            _end_line = Reader._end_line;
            _if = Reader._if;
            _line = std::move(Reader._line);
        }

        explicit reader(std::ifstream &&) = delete;

        explicit reader(std::ifstream &IfStream) noexcept: _if(&IfStream)
        { }

        explicit reader(std::ifstream *IfStream) noexcept: _if(IfStream)
        { }

        ~reader() = default;

        [[nodiscard]] std::ifstream &get() noexcept
        {
            return *_if;
        }

        [[nodiscard]] const std::ifstream &get() const noexcept
        {
            return *_if;
        }

        std::string &read() noexcept
        {
            _end_line = static_cast<bool>(std::getline(*_if, _line));
            return _line;
        }

        explicit operator bool() noexcept
        {
            _end_line = static_cast<bool>(std::getline(*_if, _line));
            return _end_line;
        }

        [[nodiscard]] const std::string &line() const noexcept
        {
            return _line;
        }

        [[nodiscard]] std::string &line() noexcept
        {
            return _line;
        }

        auto begin() noexcept
        {
            return ++Iterator(_if, _end_line);
        }

        auto end() noexcept
        {
            return Iterator(_if, false);
        }


    };
}

std::ostream &operator<<(std::ostream &Of, const babel::ITERATOR::reader &Reader) noexcept
{
    Of << Reader.line();
    return Of;
}

#endif