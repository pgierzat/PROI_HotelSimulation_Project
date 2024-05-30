#include "catch_amalgamated.hpp"
#include "../src/json_converters/JSON_amount.hpp"

TEST_CASE("Test JSONAmount")
{
    SECTION("regular")
    {
        auto amount = Amount{12, 57};
        auto j = JSONAmount::write(amount);
        auto read_amount = JSONAmount::read(j);
        REQUIRE( amount == read_amount );
    }
    
    SECTION("zero dollars")
    {
        auto amount = Amount{0, 57};
        auto j = JSONAmount::write(amount);
        auto read_amount = JSONAmount::read(j);
        REQUIRE( amount == read_amount );
    }

    SECTION("zero cents")
    {
        auto amount = Amount{12, 0};
        auto j = JSONAmount::write(amount);
        auto read_amount = JSONAmount::read(j);
        REQUIRE( amount == read_amount );
    }

    SECTION("one digit cents")
    {
        auto amount = Amount{12, 5};
        auto j = JSONAmount::write(amount);
        auto read_amount = JSONAmount::read(j);
        REQUIRE( amount == read_amount );
    }
}
