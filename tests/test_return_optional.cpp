#include <catch.hpp>


#include "../include/return_optional.cxx"
#include "../include/utils/void_optional.cxx"

#include <optional>

using namespace alg;



TEST_CASE("Make a function return an optional", "[return_optional]") {
    SECTION("Convert functor's return type to an optional") {
        auto example = return_optional {
            []() -> int { return 5; }
        };

        REQUIRE( static_cast<bool>(example()) );
        REQUIRE( *(example()) == 5 );
        REQUIRE(std::is_same_v<
            decltype(example()),
            std::optional<int>
        >);

        auto example2 = return_optional {
            []{}
        };

        REQUIRE( static_cast<bool>(example()) );
        REQUIRE(std::is_same_v<
            decltype(example2()),
            utils::void_optional
        >);
    }
}
