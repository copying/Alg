#ifndef ALG__ALGORITHM__CXX
#define ALG__ALGORITHM__CXX

#include <type_traits>
#include <utility>

namespace alg{
    template <typename Alg>
    struct Algorithm {
    private:
        template<typename T, typename = void, typename ... Ts>
        struct is_default_callable_ : std::false_type {};

        template<typename T, typename ... Ts>
        struct is_default_callable_ <
            T,
            std::void_t<decltype(T::default_(std::declval<Ts>()...))>,
            Ts...
        > : std::true_type {};

        template <typename T, typename ... Ts>
        static constexpr auto const is_default_callable = is_default_callable_<T, void, Ts...>::value;

    public:
        template <typename ... Args>
        constexpr decltype(auto) operator()(Args && ... args) const
        {
            if constexpr ( is_default_callable<Alg, Args...> )
                return Alg::default_(std::forward<Args>(args)...);
            else
                return;
        }
    };
}

#endif // ALG__ALGORITHM__CXX
