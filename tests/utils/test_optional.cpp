#include <catch.hpp>


#include "../../include/utils/void_optional.cxx"
#include "../../include/utils/optional.cxx"

#include <type_traits>
#include <optional>


using namespace alg::utils;

struct A {};




TEST_CASE("is_optional checks if a type is of the type std::optional", "[is_optional]") {
    SECTION("a few basic types") {
        REQUIRE_FALSE(is_optional_v<void>);
        REQUIRE_FALSE(is_optional_v<int>);
        REQUIRE_FALSE(is_optional_v<float>);
        REQUIRE_FALSE(is_optional_v<A>);
    }

    SECTION("basic optional types") {
        REQUIRE(is_optional_v<std::optional<int>>);
        REQUIRE(is_optional_v<std::optional<float>>);
        REQUIRE(is_optional_v<std::optional<A>>);
    }

    SECTION("cv qualified types") {
        REQUIRE_FALSE(is_optional_v<const int>);
        REQUIRE_FALSE(is_optional_v<const float>);
        REQUIRE_FALSE(is_optional_v<const A>);

        REQUIRE_FALSE(is_optional_v<const int&>);
        REQUIRE_FALSE(is_optional_v<const float&>);
        REQUIRE_FALSE(is_optional_v<const A&>);

        REQUIRE_FALSE(is_optional_v<volatile int>);
        REQUIRE_FALSE(is_optional_v<volatile float>);
        REQUIRE_FALSE(is_optional_v<volatile A>);

        REQUIRE(is_optional_v<const std::optional<int>&>);
        REQUIRE(is_optional_v<const std::optional<float>&>);
        REQUIRE(is_optional_v<const std::optional<A>&>);
    }

    SECTION("void") {
        REQUIRE_FALSE(is_optional_v<void>);
        REQUIRE(is_optional_v<void_optional>);
    }
}




TEST_CASE("make_optional returns the optional type of the given type", "[make_optional]") {
    SECTION("basic types") {
        REQUIRE(std::is_same_v<make_optional_t<int>, std::optional<int>>);
        REQUIRE(std::is_same_v<make_optional_t<float>, std::optional<float>>);
        REQUIRE(std::is_same_v<make_optional_t<A>, std::optional<A>>);
    }

    SECTION("cv qualified types") {
        REQUIRE(std::is_same_v<make_optional_t<const int>, std::optional<int>>);
        REQUIRE(std::is_same_v<make_optional_t<const float>, std::optional<float>>);
        REQUIRE(std::is_same_v<make_optional_t<const A>, std::optional<A>>);

        REQUIRE(std::is_same_v<make_optional_t<const int&>, std::optional<int>>);
        REQUIRE(std::is_same_v<make_optional_t<const float&>, std::optional<float>>);
        REQUIRE(std::is_same_v<make_optional_t<const A&>, std::optional<A>>);

        REQUIRE(std::is_same_v<make_optional_t<volatile int>, std::optional<int>>);
        REQUIRE(std::is_same_v<make_optional_t<volatile float>, std::optional<float>>);
        REQUIRE(std::is_same_v<make_optional_t<volatile A>, std::optional<A>>);
    }

    SECTION("void") {
        REQUIRE(std::is_same_v<make_optional_t<void>, void_optional>);
    }
}



TEST_CASE("remove_optional returns the type of the given optional", "[remove_optional]") {
    //*
    SECTION("basic types") {
        REQUIRE(std::is_same_v<remove_optional_t<std::optional<int>>, int>);
        REQUIRE(std::is_same_v<remove_optional_t<std::optional<float>>, float>);
        REQUIRE(std::is_same_v<remove_optional_t<std::optional<A>>, A>);
    }

    SECTION("cv qualified types") {
        REQUIRE(std::is_same_v<remove_optional_t<const std::optional<int>>, int>);
        REQUIRE(std::is_same_v<remove_optional_t<const std::optional<float>>, float>);
        REQUIRE(std::is_same_v<remove_optional_t<const std::optional<A>>, A>);

        REQUIRE(std::is_same_v<remove_optional_t<const std::optional<int>&>, int>);
        REQUIRE(std::is_same_v<remove_optional_t<const std::optional<float>&>, float>);
        REQUIRE(std::is_same_v<remove_optional_t<const std::optional<A>&>, A>);

        REQUIRE(std::is_same_v<remove_optional_t<volatile std::optional<int>>, int>);
        REQUIRE(std::is_same_v<remove_optional_t<volatile std::optional<float>>, float>);
        REQUIRE(std::is_same_v<remove_optional_t<volatile std::optional<A>>, A>);
    }
//*/
    SECTION("void") {
        static_assert(std::is_same_v<std::decay_t<void_optional>, void_optional>);
        REQUIRE(std::is_same_v<remove_optional_t<void_optional>, void>);
    }
}
