#ifndef ALG__fallback_CXX
#define ALG__fallback_CXX

#include "utils/void_optional.cxx"
#include "utils/optional.cxx"
#include "call_if.cxx"


namespace alg {
    template <typename ... Funcs>
    struct fallback {
        template<typename ... Args>
        constexpr utils::void_optional operator()(Args && ... args) const {
            return std::nullopt;
        }
    };

    template <typename Func>
    struct fallback<Func> : make_functor_optional_t<Func> {
    private:
        using OpFunc = make_functor_optional_t<Func>;

    public:
        template<typename ... Args>
        constexpr inline auto operator()(Args && ... args) const {
            return OpFunc::operator()(std::forward<Args>(args)...);
        }
    };

    template <typename Func, typename ... Funcs>
    struct fallback<Func, Funcs...> : make_functor_optional_t<Func>, fallback<Funcs...> {
    private:
        using OpFunc = make_functor_optional_t<Func>;
        using Next = fallback<Funcs...>;

    public:
        template<typename ... Args>
        constexpr inline auto operator()(Args && ... args) const {

            // Do this type work together
            constexpr bool valid_types = std::is_convertible_v<
                decltype(Next::operator()(std::declval<Args>()...)),
                decltype(OpFunc::operator()(std::declval<Args>()...))
            >;
            static_assert(
                valid_types,
                "The functors return different, uncompatible types."
            );


            if constexpr (valid_types) { // prevents long unreadable error (we already have the static_assert)
                auto value = OpFunc::operator()(std::forward<Args>(args)...);
                if (value)
                    return value;
                else
                    return Next::operator()(std::forward<Args>(args)...);
            }
        }
    };


    template <typename ... Ts>
    fallback(Ts && ...) -> fallback<std::decay_t<Ts>...>;
}

#endif // ALG__fallback_CXX
