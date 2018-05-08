#ifndef ALG__UTILS__OPTIONAL__CXX
#define ALG__UTILS__OPTIONAL__CXX

#include "void_optional.cxx"

#include <type_traits>
#include <optional>

// is_optional
namespace alg::utils {
    namespace {
        template<typename O, typename = void>
        struct is_optional_ : std::false_type {};

        template<template <typename> typename O, typename T>
        struct is_optional_<
            O<T>,
            std::enable_if_t<
                std::is_same_v<
                    O<T>,
                    std::optional<T>
                >
            >
        > : std::true_type {};

        template<>
        struct is_optional_<void_optional> : std::true_type {};
    }


    template <typename T>
    using is_optional = is_optional_<std::decay_t<T>>;

    template <typename T>
    [[maybe_unused]]
    constexpr auto const is_optional_v = is_optional<T>::value;
}



// make_optional
namespace alg::utils {
    namespace {
        template<typename T>
        using make_optional_ =
            std::conditional<
                is_optional_v<T>,
                T,
                std::conditional_t<
                    std::is_same_v<
                        T,
                        void
                    >,
                    void_optional,
                    std::optional<T>
                >
            >;
    }

    template<typename T>
    using make_optional = make_optional_<std::decay_t<T>>;

    template<typename T>
    using make_optional_t = typename make_optional<T>::type;
}



#endif // ALGUTILS__OPTIONAL__CXX
