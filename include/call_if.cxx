#ifndef ALG__CALL_IF__CXX
#define ALG__CALL_IF__CXX

#include "utils/optional.cxx"

#include <type_traits>
#include <utility>

namespace alg {
    struct TrueFunctor {
        template <typename ... Args>
        constexpr bool operator()(Args && ...) const noexcept {
            return true;
        }
    };

    template <typename Functor, typename Condition = TrueFunctor>
    struct call_if : Functor, Condition {
    private:

        template <typename BasicReturn>
        using Return = utils::make_optional_t<BasicReturn>;

    public:
        template <typename Func>
        constexpr call_if(Func&& func) noexcept(
            noexcept(Functor{std::forward<Func>(std::declval<Func>())})
        )
        : Functor{std::forward<Func>(func)},
          TrueFunctor{}
        {}
        template <typename Func, typename Cond>
        constexpr call_if(Func&& func, Cond&& cond) noexcept(
            noexcept(Functor{std::forward<Func>(std::declval<Func>())})
            && noexcept(Condition{std::forward<Cond>(std::declval<Cond>())})
        )
        : Functor{std::forward<Func>(func)},
          Condition{std::forward<Cond>(cond)}
        {}

        template <typename ... Args>
        constexpr inline auto operator()(Args && ... args) const noexcept(
            noexcept(std::declval<Condition>()(std::declval<Args>()...))
            && noexcept(std::declval<Functor>()(std::declval<Args>()...))
        )
        -> Return<decltype(Functor::operator()(std::declval<Args>()...))>
        {
            using FR = decltype(Functor::operator()(std::declval<Args>()...));

            if (Condition::operator()(std::forward<Args>(args)...)) {
                if constexpr ( std::is_same_v<FR, void> ) {
                    Functor::operator()(std::forward<Args>(args)...);
                    return {};
                } else {
                    return Functor::operator()(std::forward<Args>(args)...);
                }
            } else {
                return std::nullopt;
            }
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
