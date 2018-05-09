#ifndef ALG__OVERLOAD__CXX
#define ALG__OVERLOAD__CXX


#include <type_traits>


namespace alg {
    template <typename ... Funcs>
    struct overload_ : Funcs... {
        using Funcs::operator()...;
    };
    template <typename ... Args>
    overload_(Args && ...) -> overload_<std::decay_t<Args>...>;


    template <typename ... Funcs>
    struct ovld : Funcs... {
        using Funcs::operator()...;
    };
    template <typename ... Args>
    ovld(Args && ...) -> ovld<std::decay_t<Args>...>;


    template <typename ... Funcs>
    struct ol : Funcs... {
        using Funcs::operator()...;
    };
    template <typename ... Args>
    ol(Args && ...) -> ol<std::decay_t<Args>...>;
}

#endif // ALG__OVERLOAD__CXX
