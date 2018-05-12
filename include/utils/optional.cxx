#ifndef ALG__UTILS__OPTIONAL__CXX
#define ALG__UTILS__OPTIONAL__CXX

#include "void_optional.cxx"

#include <type_traits>
#include <optional>

// is_optional
namespace alg::utils {
    namespace {
        template<typename T>
        struct is_optional_ : std::false_type {};
        template<typename T>
        struct is_optional_<std::optional<T>> : std::true_type {};
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
        template <typename T>
        struct make_optional_ {
            using type = std::optional<T>;
        };
        template <typename T>
        struct make_optional_<std::optional<T>> {
            using type = std::optional<T>;
        };
        template <>
        struct make_optional_<void> {
            using type = void_optional;
        };
    }

    template<typename T>
    using make_optional = make_optional_<std::decay_t<T>>;

    template<typename T>
    using make_optional_t = typename make_optional<T>::type;
}



// remove_optional
namespace alg::utils {
    namespace {
        template <typename T>
        struct remove_optional_ {
            using type = T;
        };
        template <typename T>
        struct remove_optional_<std::optional<T>> {
            using type = T;
        };
        template <>
        struct remove_optional_<void_optional> {
            using type = void;
        };
    }

    template<typename T>
    using remove_optional = remove_optional_<std::decay_t<T>>;

    template<typename T>
    using remove_optional_t = typename remove_optional<T>::type;
}



#endif // ALGUTILS__OPTIONAL__CXX
