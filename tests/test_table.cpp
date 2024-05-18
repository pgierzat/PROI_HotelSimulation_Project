#include "catch_amalgamated.hpp"
#include "../src/types/table.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test Table")
{
    Table table{"25"};
    const auto& clients = table.get_clients();
    Guest guest1{"name1"};
    Guest guest2{"name2"};

    SECTION("init")
    {
        REQUIRE( table.get_number() == "25" );
        REQUIRE( clients.empty() );
    }

    SECTION("assign client")
    {
        table.assign_client(guest1);
        std::vector<const Guest*> exp{&guest1};
        REQUIRE(clients == exp);
        table.assign_client(guest2);
        exp.push_back(&guest2);
        REQUIRE(clients == exp);
    }

    SECTION("assign same client")
    {
        table.assign_client(guest1);
        REQUIRE_THROWS_AS(table.assign_client(guest1), DuplicateClientError);
    }

    SECTION("unassign clients")
    {
        table.assign_client(guest1);
        table.assign_client(guest2);
        table.unassign_clients();
        REQUIRE(clients.empty());
    }
}