#include <catch.hpp>


#include "../../include/utils/priority.cxx"



using namespace alg::utils;


constexpr int test(priority<0>) noexcept { return 0; }
constexpr int test(priority<1>) noexcept { return 1; }
constexpr int test(priority<2>) noexcept { return 2; }

TEST_CASE("priority used to prioritize a function", "[priority]") {
    REQUIRE( test(priority<2>{}) == 2 );
    REQUIRE( test(priority<1>{}) == 1 );
    REQUIRE( test(priority<0>{}) == 0 );
    
    REQUIRE( test(priority<10>{}) == 2 );
}
