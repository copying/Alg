#ifndef ALG__PRIORITIZE__CXX
#define ALG__PRIORITIZE__CXX

#include "utils/priority.cxx"


namespace alg {
    template <typename ... Functors>
    struct prioritize {};

    template <typename Functor>
    struct prioritize<Functor> : Functor {
        template <typename ... Args>
        constexpr inline decltype(auto) call(utils::priority<0>&&, Args && ... args) const noexcept (
            noexcept(std::declval<Functor>()(std::declval<Args>()...))
        )
        {
            return Functor::operator()(std::forward<Args>(args)...);
        }

        template <typename ... Args>
        constexpr inline decltype(auto) operator()(Args && ... args) const noexcept (
            noexcept(std::declval<Functor>()(std::declval<Args>()...))
        )
        {
            return Functor::operator()(std::forward<Args>(args)...);
        }
    };

    template <typename Functor, typename ... Functors>
    struct prioritize<Functor, Functors...> : Functor, prioritize<Functors...> {
        using prioritize<Functors...>::call;

        template <typename ... Args>
        constexpr inline auto call(utils::priority<sizeof...(Functors)>&&, Args && ... args) const noexcept (
            noexcept(std::declval<Functor>()(std::declval<Args>()...))
        )
        -> decltype(Functor::operator()(std::declval<Args>()...)) {
            return Functor::operator()(std::forward<Args>(args)...);
        }

        template <typename ... Args>
        constexpr inline decltype(auto) operator()(Args && ... args) const noexcept (
            noexcept(std::declval<prioritize<Functor, Functors...>>().call(std::declval<utils::priority<sizeof...(Functors)>>(), std::declval<Args>()...))
        )
        {
            return call(utils::priority<sizeof...(Functors)>{}, std::forward<Args>(args)...);
        }
    };

    template <typename ... Functors>
    prioritize(Functors && ...) -> prioritize<std::decay_t<Functors>...>;
}

#endif // ALG__PRIORITIZE__CXX
