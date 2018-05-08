#ifndef ALGORITHMS__UTILS__PRIORITY
#define ALGORITHMS__UTILS__PRIORITY

#include <cstdint>

namespace alg::utils {
    template<std::uintmax_t n>
    struct priority : priority<n-1> {};

    template<>
    struct priority<0> {};
}

#endif // ALGORITHMS__UTILS__PRIORITY
