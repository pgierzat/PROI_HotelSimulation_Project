#include "catch_amalgamated.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/functions/equal_operators.hpp"

TEST_CASE("test GuestSystem")
{
    GuestSystem g_system{};
    Guest guest1{"id1", "name1"};
    Guest guest2{"id2", "name2"};
    g_system.add_guest(guest1);
    g_system.add_guest(guest2);

    SECTION("add guest")
    {
        std::vector expected{guest1, guest2};
        REQUIRE( g_system.get_guests() == expected );
    }

    SECTION("find by name hit")
    {
        auto found1 = (g_system.find_by_id("id1")).value();
        REQUIRE( *found1 == guest1 );
    }

    SECTION("find by name miss")
    {
        REQUIRE( !g_system.find_by_id("id3").has_value() );
    }

    SECTION("remove guest")
    {
        g_system.remove_guest(guest1);
        std::vector<Guest> expected{guest2};
        REQUIRE( g_system.get_guests() == expected );
    }
}
