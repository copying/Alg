#include <catch.hpp>


#include "../include/algorithm.cxx"
#include "../include/overload.cxx"


using namespace alg;





struct Power2 : Algorithm<Power2> {

    // Using multiplication and a loop
    static constexpr auto mul = [](unsigned x) {
        unsigned r = 1;
        for (unsigned i = 0; i<x; ++i) {
            r = r*2;
        }
        return r;
    };

    // Using left shift operator
    static constexpr auto shift = [](unsigned x) {
        return 1<<x;
    };

    // For containers
    static constexpr auto multi_in_place = [](auto& container) {
        for (auto& element : container) {
            element = 1<<element;
        }
    };

    // Set the default
    static constexpr auto default_ = overload_ {
        multi_in_place,
        shift
    };
};
[[maybe_unused]] constexpr Power2 const power2;



bool g = false;
struct SideEffect : Algorithm<SideEffect> {
    static constexpr auto default_ = []() constexpr { return g=true; };
};
[[maybe_unused]] constexpr SideEffect const side_effect;



TEST_CASE("Make a function return an optional", "[return_optional]") {
    SECTION("Regular use") {
        REQUIRE( power2(1) == 2 );
        REQUIRE( power2.mul(1) == 2 );
        REQUIRE( power2.shift(1) == 2 );
        REQUIRE( power2.default_(1) == 2 );

        REQUIRE_FALSE( g );
        side_effect();
        REQUIRE( g );
    }
}
