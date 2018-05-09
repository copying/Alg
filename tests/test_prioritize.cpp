#include <catch.hpp>


#include "../include/prioritize.cxx"

#include <type_traits>



using namespace alg;


TEST_CASE("prioritize a function from another", "[prioritize]") {
    SECTION("Regular usage") {
        auto example = prioritize {
            [](int i) constexpr -> int {
                return 0;
            },
            [](int i) constexpr -> int {
                return 1;
            }
        };

        REQUIRE(example(2) == 0);
    }

    SECTION("Prioritize methods") {
        auto example = prioritize {
            [](int i) constexpr -> void {},
            [](int i) constexpr -> int {
                return 1;
            }
        };

        REQUIRE( std::is_same_v<
            decltype(example(2)),
            void
        >);
    }

    SECTION("Prioritize without arguments") {
        auto example = prioritize {
            []() constexpr -> void {},
            []() constexpr -> int {
                return 1;
            }
        };

        REQUIRE( std::is_same_v<
            decltype(example()),
            void
        >);
    }

    SECTION("Check constexpr-ness") {
        constexpr auto example = prioritize {
            []() constexpr -> void {},
            [](int i) constexpr -> int {
                return i*2+1;
            }
        };

        constexpr int const result = example(3);

        REQUIRE( result == 7 );
    }

    SECTION("Check noexcept-ness") {
        constexpr auto example = prioritize {
            []() constexpr noexcept -> void {},
            [](int i) constexpr noexcept -> int {
                return i*2+1;
            }
        };

        REQUIRE( noexcept(example()) );
        REQUIRE( noexcept(example(5)) );
    }
}
