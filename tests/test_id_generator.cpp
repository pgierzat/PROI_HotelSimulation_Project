#include "catch_amalgamated.hpp"
#include "../src/auxiliary/id_generator.hpp"

TEST_CASE("Test IDGenerator")
{
    auto id_gen = IDGenerator();

    SECTION("simple")
    {
        REQUIRE(id_gen.generate_id() == "1");
        REQUIRE(id_gen.generate_id() == "2");
    }
    
    SECTION("forbid")
    {
        id_gen.forbid_id("2");
        REQUIRE(id_gen.generate_id() == "1");
        REQUIRE(id_gen.generate_id() == "3");
    }
}
