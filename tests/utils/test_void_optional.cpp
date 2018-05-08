#include <catch.hpp>


#include "../../include/utils/void_optional.cxx"

#include <type_traits>



using namespace alg::utils;

TEST_CASE("void_optional mimics std::optional but for void", "[void_optional]") {
    SECTION("Success") {
        auto example = []() -> void_optional {};

        REQUIRE( example().has_value() );
        REQUIRE( static_cast<bool>(example()) );
        REQUIRE( std::is_same_v<
            decltype(*(example())),
            void
        >);
    }

    SECTION("Failure") {
        auto example = []() -> void_optional {
            return std::nullopt;
        };

        REQUIRE_FALSE( example().has_value() );
        REQUIRE_FALSE( static_cast<bool>(example()) );
        REQUIRE( std::is_same_v<
            decltype(*(example())),
            void
        >);
    }
}
