#ifndef ALG__CALL_IF__CXX
#define ALG__CALL_IF__CXX

#include "utils/optional.cxx"

#include <type_traits>
#include <utility>

namespace alg {
    struct TrueFunctor {
        template <typename ... Ts>
        constexpr bool operator()(Ts && ...) const {
            return true;
        }
    };

    template <typename Functor, typename Condition = TrueFunctor>
    struct call_if : Functor, Condition {
    private:

        template <typename BasicReturn>
        using Return = utils::make_optional_t<BasicReturn>;

    public:
        template <typename ... Ts>
        constexpr auto operator()(Ts && ... ts) const
        -> Return<decltype(Functor::operator()(std::declval<Ts>()...))>
        {
            if (Condition::operator()(std::forward<Ts>(ts)...))
                if constexpr ( std::is_same_v<decltype(Functor::operator()(std::declval<Ts>()...)), void> )
                    Functor::operator()(std::forward<Ts>(ts)...);
                else
                    return Functor::operator()(std::forward<Ts>(ts)...);
            else
                return std::nullopt;
        }
    };


    template <typename Functor>
    call_if (Functor &&) -> call_if<std::decay_t<Functor>, TrueFunctor>;

    template <typename Functor, typename Condition>
    call_if (Functor &&, Condition &&) -> call_if<std::decay_t<Functor>, std::decay_t<Condition>>;


    template <typename Functor>
    struct make_functor_optional_t : call_if<Functor> {};

    template <typename Functor>
    make_functor_optional_t (Functor &&) -> make_functor_optional_t<std::decay_t<Functor>>;

}

#endif // ALG__C  ALL_IF__CXX
