#ifndef babel_CONCEPTS
#define babel_CONCEPTS

#include <type_traits>

namespace babel::CONCEPTS {
    namespace TYPE_TRAITS {
        template<typename T>
        using decay_t = typename std::decay_t<T>;
        template<typename T, typename U>
        static constexpr bool is_same_v = std::is_same_v<decay_t<T>, decay_t<U> >;
        template<typename T, typename U>
        static constexpr bool is_convertible_v = std::is_convertible_v<decay_t<T>, decay_t<U> >;
        template<typename T>
        static constexpr bool is_destructible_v = std::is_destructible_v<decay_t<T>>;
    }
    template<typename LHS, typename RHS>
    concept IS_SAME_CONVERTIBLE = TYPE_TRAITS::is_same_v<LHS, RHS> || TYPE_TRAITS::is_convertible_v<LHS, RHS>;

    template<typename LHS, typename RHS>
    concept IS_SAME = TYPE_TRAITS::is_same_v<LHS, RHS>;

    template<typename LHS, typename RHS>
    concept IS_NOT_SAME = !TYPE_TRAITS::is_same_v<LHS, RHS>;

    template<typename LHS, typename RHS>
    concept IS_CONVERTIBLE = TYPE_TRAITS::is_convertible_v<LHS, RHS>;

    template<typename T>
    concept IS_POINTER = std::is_pointer_v<T>;

    template<typename T>
    concept IS_NOT_POINTER = !std::is_pointer_v<T>;

    template<typename T>
    concept IS_NOT_ANY_VOID = !TYPE_TRAITS::is_same_v<T, void*> && !TYPE_TRAITS::is_same_v<T, void>;

    template<typename T>
    concept IS_DESTRUCTIBLE = TYPE_TRAITS::is_destructible_v<T>;

    template<typename T>
    concept IS_SIGNED = std::is_signed_v<TYPE_TRAITS::decay_t<T>>;

    template<typename T>
    concept IS_UNSIGNED = std::is_unsigned_v< TYPE_TRAITS::decay_t<T> >;

    template<typename T>
    concept IS_FLOATING_POINT = std::is_floating_point_v< TYPE_TRAITS::decay_t<T> >;
    template<typename T>
    concept IS_ARITHMETIC = requires(T obj)
    {
        obj + obj;
        obj - obj;
        obj * obj;
        obj / obj;
    };

    template<typename T>
    concept IS_CONTAINER =
            requires(T cont)
            {
                std::begin(cont);
                std::end(cont);
                //cont[0];
                cont.size();
            };

    template<typename T>
    concept IS_LIKE_VECTOR =
    requires(T cont)
    {
        std::begin(cont);
        std::end(cont);
        cont[0];
        cont.size();
    };
    namespace MEMBER
    {
        template<typename T>
        concept HAS_SIZE =
        requires(const T object){
            object.size();
        }
        ||
        requires(const T object){
            object->size();
        };

        template<typename T>
        concept HAS_CLOSE =
        requires(T &object){
            object.close();
        }
        ||
        requires(T &object){
            object->close();
        };

        template<typename T>
        concept HAS_GET =
        requires(T object){
            object.get();
        }
        ||
        requires(T object){
            object->get();
        };
    }
    template<typename Func, typename ... Args>
    concept IS_VOID_RETURN =  requires(Func func, Args...args)
    {
        { func(args...) } -> std::same_as<void>;
    };


    //Return type in container T -> can be list/vector etc.
    template<typename Vec>
    requires babel::CONCEPTS::IS_CONTAINER<Vec>
    struct type_in{
        typedef std::decay_t<decltype(*Vec{}.begin())> type;
    };
    //END
}
#endif