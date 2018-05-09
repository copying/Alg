#ifndef ALG__RETURN_OPTIONAL__CXX
#define ALG__RETURN_OPTIONAL__CXX

#include "call_if.cxx"

namespace alg {
    template <typename Functor>
    struct return_optional : call_if<Functor> {};

    template <typename Functor>
    return_optional (Functor &&) -> return_optional<std::decay_t<Functor>>;
}

#endif // ALG__RETURN_OPTIONAL__CXX
