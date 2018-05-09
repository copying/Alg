#ifndef ALG__UTILS__PRIORITY__CXX
#define ALG__UTILS__PRIORITY__CXX

#include <cstdint>

namespace alg::utils {
    template<std::uintmax_t n>
    struct priority : priority<n-1> {};

    template<>
    struct priority<0> {};
}

#endif // ALG__UTILS__PRIORITY__CXX
