// Copyright [2021] <Wojtek>"
#ifndef BABLIB_CONCEPTS_CONCEPTS_HPP_
#define BABLIB_CONCEPTS_CONCEPTS_HPP_

#include <type_traits>
#include <cstdint>
#include <iterator>

namespace babel::CONCEPTS{
    namespace TYPE_TRAITS{
        template< typename T >
        using decay_t = typename std::decay_t<T>;
        template< typename T, typename U >
        constexpr bool is_same_v = std::is_same_v<decay_t<T>, decay_t<U> >;
        template< typename T, typename U >
        constexpr bool is_convertible_v = std::is_convertible_v<decay_t<T>, decay_t<U> >;
        template< typename T >
        constexpr bool is_destructible_v = std::is_destructible_v<decay_t<T>>;
    }
    template< typename LHS, typename RHS >
    concept IS_SAME_CONVERTIBLE = TYPE_TRAITS::is_same_v<LHS, RHS> || TYPE_TRAITS::is_convertible_v<LHS, RHS>;

    template< typename LHS, typename RHS >
    concept IS_SAME = TYPE_TRAITS::is_same_v<LHS, RHS>;

    template< typename LHS, typename RHS >
    concept IS_NOT_SAME = !TYPE_TRAITS::is_same_v<LHS, RHS>;

    template< typename LHS, typename RHS >
    concept IS_CONVERTIBLE = TYPE_TRAITS::is_convertible_v<LHS, RHS>;

    template< typename T >
    concept IS_POINTER = std::is_pointer_v<T>;

    template< typename T >
    concept IS_NOT_POINTER = !std::is_pointer_v<T>;

    template< typename T >
    concept IS_NOT_ANY_VOID = !TYPE_TRAITS::is_same_v<T, void *> && !TYPE_TRAITS::is_same_v<T, void>;

    template< typename T >
    concept IS_DESTRUCTIBLE = TYPE_TRAITS::is_destructible_v<T>;

    template< typename T >
    concept IS_SIGNED = std::is_signed_v<TYPE_TRAITS::decay_t<T>>;

    template< typename T >
    concept IS_UNSIGNED = std::is_unsigned_v<TYPE_TRAITS::decay_t<T> >;

    template< typename T >
    concept IS_FLOATING_POINT = std::is_floating_point_v<TYPE_TRAITS::decay_t<T> >;
    template< typename T >
    concept IS_ARITHMETIC =
    requires(T obj)
    {
        obj + obj;
        obj - obj;
        obj * obj;
        obj / obj;
    };

    template< typename T >
    concept IS_CONTAINER =
    requires(T cont)
    {
        std::begin(cont);
        std::end(cont);
        cont.size();
    };

    template< typename T >
    concept IS_ANY_POINTER =
    requires(T ptr)
    {
        *ptr;
    }
    ||
    requires(T ptr)
    {
        // Check for unique or shared ptr
        *ptr;
        std::is_pointer_v<decltype(ptr.get())>;
    }
    ||
    requires(T ptr)
    {
        // Check for weak pointer
        ptr.lock();
        ptr.reset();
        ptr.expired();
    };


    template< typename T >
    concept IS_LIKE_VECTOR =
    requires(T cont)
    {
        std::begin(cont);
        std::end(cont);
        cont[0];
        cont.size();
    };
    namespace MEMBER{
        template< typename T >
        concept HAS_SIZE =
        requires(const T object){
            object.size();
        }
        ||
        requires(const T object){
            object->size();
        };

        template< typename T >
        concept HAS_CLOSE =
        requires(T &object){
            object.close();
        }
        ||
        requires(T &object){
            object->close();
        };

        template< typename T >
        concept HAS_GET =
        requires(T object){
            object.get();
        }
        ||
        requires(T object){
            object->get();
        };
    }  // namespace MEMBER
    template< typename Func, typename ... Args >
    concept IS_VOID_RETURN =
    requires(Func func, Args...args)
    {
        { func(args...) } -> std::same_as<void>;
    };


    // Check if function return ReturnType
    template< typename Func, typename ReturnType, typename ... Args >
    concept FUNCTION_RETURN =
    requires(Func func, Args...args)
    {
        { func(args...) } -> babel::CONCEPTS::IS_CONVERTIBLE<std::decay_t<ReturnType>>;
    };

    //Return type in container T -> can be list/vector etc.
    template< typename Vec >
    requires babel::CONCEPTS::IS_CONTAINER<Vec>
    using type_in = std::decay_t<decltype(*Vec { }.begin())>;
    //END

    template< typename ATOMIC >
    struct type_in_atomic
    {
        typedef decltype(ATOMIC()++) type;
    };

    template< uint8_t bytes, bool IsSigned = true >
    class type_of_number
    {
        static_assert(bytes > 0 && bytes <= 8 && bytes != 3 && bytes != 5 && bytes != 6 && bytes != 7);

        constexpr static auto babel_type_of() noexcept
        {
            if constexpr ( IsSigned )
            {
                if constexpr ( bytes == 1 )
                {
                    return static_cast<int8_t>(0);
                }
                if constexpr ( bytes == 2 )
                {
                    return static_cast<int16_t>(0);
                }

                if constexpr ( bytes == 4 )
                {
                    return static_cast<int32_t>(0);
                }

                if constexpr ( bytes == 8 )
                {
                    return static_cast<int64_t>(0);
                }
            }

            if constexpr ( !IsSigned )
            {
                if constexpr ( bytes == 1 )
                {
                    return static_cast<uint8_t>(0);
                }
                if constexpr ( bytes == 2 )
                {
                    return static_cast<uint16_t>(0);
                }

                if constexpr ( bytes == 4 )
                {
                    return static_cast<uint32_t>(0);
                }

                if constexpr ( bytes == 8 )
                {
                    return static_cast<uint64_t>(0);
                }
            }
        }

    public:
        typedef decltype(babel_type_of()) type;
    };

    using IteratorAddType = type_of_number<sizeof(void *)>::type;
}  // namespace babel::CONCEPTS
#endif  // BABLIB_CONCEPTS_CONCEPTS_HPP_
