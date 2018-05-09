#ifndef ALG__FALLBACK__CXX
#define ALG__FALLBACK__CXX

#include "utils/void_optional.cxx"
#include "utils/optional.cxx"
#include "return_optional.cxx"

#include <type_traits>
#include <optional>

namespace alg {
    template <typename ... Funcs>
    struct fallback {
        template<typename ... Args>
        constexpr utils::void_optional operator()(Args && ... args) const noexcept {
            return std::nullopt;
        }
    };

    template <typename Func>
    struct fallback<Func> : return_optional<Func> {
    private:
        using OpFunc = return_optional<Func>;

    public:
        template<typename ... Args>
        constexpr inline auto operator()(Args && ... args) const noexcept(
            noexcept(std::declval<OpFunc>()(std::declval<Args>()...))
        )
        {
            return OpFunc::operator()(std::forward<Args>(args)...);
        }
    };

    template <typename Func, typename ... Funcs>
    struct fallback<Func, Funcs...> : return_optional<Func>, fallback<Funcs...> {
    private:
        using OpFunc = return_optional<Func>;
        using Next = fallback<Funcs...>;

    public:
        template<typename ... Args>
        constexpr inline auto operator()(Args && ... args) const noexcept(
            noexcept(std::declval<OpFunc>()(std::declval<Args>()...))
            && noexcept(std::declval<Next>()(std::declval<Args>()...))
        )
        {

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

#endif // ALG__FALLBACK__CXX
