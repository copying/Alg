#ifndef ALG__UTILS__OPTIONAL_VOID__CXX
#define ALG__UTILS__OPTIONAL_VOID__CXX

#include <optional>

namespace alg::utils {
    struct void_optional {
        constexpr void_optional() noexcept
        : _has_value{true}
        {}
        constexpr void_optional(std::nullopt_t) noexcept
        : _has_value{false}
        {}

        constexpr explicit operator bool() const noexcept {
            return _has_value;
        }
        constexpr bool has_value() const noexcept {
            return _has_value;
        }

        constexpr void operator*() const noexcept {}
    private:
        bool _has_value;
    };
}


#endif // ALG__UTILS__OPTIONAL_VOID__CXX
