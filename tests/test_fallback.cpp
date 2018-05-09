#include <catch.hpp>


#include "../include/fallback.cxx"
#include "../include/utils/void_optional.cxx"

#include <optional>



using namespace alg;


TEST_CASE("fallsback to the next functor until it succeeds or has no more functors", "[fallback]") {
    SECTION("Regular usage") {
        auto example = fallback {
            []() -> std::optional<int> {
                return std::nullopt;
            },
            []() -> int {
                return 0;
            }
        };

        REQUIRE( static_cast<bool>(example()) );
        REQUIRE( *(example()) == 0 );
    }

    SECTION("No result") {
        auto example = fallback {
            []() -> std::optional<int> {
                return std::nullopt;
            }
        };

        REQUIRE_FALSE( static_cast<bool>(example()) );
    }


    SECTION("No functors") {
        auto example = fallback {};

        REQUIRE_FALSE( static_cast<bool>(example()) );
    }

    SECTION("Method") {
        bool is_set = false;

        auto example = fallback {
            []() -> utils::void_optional { return std::nullopt; },
            [&] {
                is_set = true;
            }
        };

        REQUIRE( static_cast<bool>(example()) );
        REQUIRE( is_set );
    }
}
