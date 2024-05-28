#include "catch_amalgamated.hpp"
#include "../src/types/guest.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/types/table.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test Table")
{   
    auto g_system = GuestSystem{};
    g_system.add_guest(Guest{"id1", "name1"});
    g_system.add_guest(Guest{"id2", "name2"});
    const auto& guest1 = g_system.get_by_id("id1");
    const auto& guest2 = g_system.get_by_id("id2");
    Table::set_g_system(g_system);      // temporary
    Table table{"25"};

    SECTION("init")
    {
        REQUIRE( table.get_number() == "25" );
        auto clients = table.get_clients();
        REQUIRE( clients.empty() );
    }

    SECTION("assign client")
    {
        table.assign_client(guest1);
        std::vector<const Guest*> exp{&guest1};
        auto clients = table.get_clients();
        REQUIRE(clients == exp);
        table.assign_client(guest2);
        exp.push_back(&guest2);
        clients = table.get_clients();
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
        auto clients = table.get_clients();
        REQUIRE(clients.empty());
    }
}