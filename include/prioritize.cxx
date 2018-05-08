#ifndef ALG__PRIORITIZE__CXX
#define ALG__PRIORITIZE__CXX

#include "utils/priority.cxx"


namespace alg {
    template <typename ... Functors>
    struct prioritize {};

    template <typename Functor>
    struct prioritize<Functor> : Functor {
        template <typename ... Ts>
        constexpr inline auto call(utils::priority<0>&&, Ts && ... ts) const {
            return Functor::operator()(std::forward<Ts>(ts)...);
        }

        template <typename ... Ts>
        constexpr inline auto operator()(Ts && ... ts) const {
            return Functor::operator()(std::forward<Ts>(ts)...);
        }
    };

    template <typename Functor, typename ... Functors>
    struct prioritize<Functor, Functors...> : Functor, prioritize<Functors...> {
        using prioritize<Functors...>::call;

        template <typename ... Ts>
        constexpr inline auto call(utils::priority<sizeof...(Functors)>&&, Ts && ... ts) const
        -> decltype(Functor::operator()(std::declval<Ts>()...)) {
            return Functor::operator()(std::forward<Ts>(ts)...);
        }

        template <typename ... Ts>
        constexpr inline auto operator()(Ts && ... ts) const {
            return call(utils::priority<sizeof...(Functors)>{}, std::forward<Ts>(ts)...);
        }
    };

    template <typename ... Functors>
    prioritize(Functors && ...) -> prioritize<std::decay_t<Functors>...>;
}

#endif // ALG__PRIORITIZE__CXX
