#include <catch.hpp>


#include "../include/overload.cxx"

using namespace alg;

TEST_CASE("Overload overloads callable objects into a new one", "[overload]") {
    constexpr auto example = overload_ {
        []() constexpr noexcept -> void {},
        [](int i) constexpr noexcept -> int {
            return i*2+1;
        }
    };

    SECTION("Regular use") {
        REQUIRE( example(3) == 7 );
    }

    SECTION("Check constexpr-ness") {
        constexpr int i = example(3);
        REQUIRE( i == 7 );
    }

    SECTION("Check noexcept-ness") {
        REQUIRE(noexcept(example()));
    }

    SECTION("Check variants") {
        constexpr auto a = ol {
            []() constexpr noexcept -> void {},
            [](int i) constexpr noexcept -> int {
                return i*2+1;
            }
        };
        REQUIRE( a(3) == example(3) );
/*
        constexpr auto b = ovld {
            []() constexpr noexcept -> void {},
            [](int i) constexpr noexcept -> int {
                return i*2+1;
            }
        };
        REQUIRE( b(3) == example(3) );
*/
    }
}
