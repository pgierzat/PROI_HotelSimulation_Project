#include "catch_amalgamated.hpp"
#include "../src/systems/guest_system.hpp"

TEST_CASE("test GuestSystem")
{
    GuestSystem g_system{};
    Guest guest1{"name1"};
    Guest guest2{"name2"};
    g_system.add_guest(guest1);
    g_system.add_guest(guest2);
    auto guests = g_system.get_guests();

    SECTION("add guest")
    {
        std::vector expected{guest1, guest2};
        REQUIRE( guests == expected );
    }

    SECTION("find by name hit")
    {
        auto found1 = (g_system.find_by_name("name1")).value();
        REQUIRE( found1.get_name() == "name1" );
    }

    SECTION("find by name miss")
    {
        REQUIRE( !g_system.find_by_name("name3").has_value() );
    }

    SECTION("remove guest")
    {
        g_system.remove_guest(guest1);
        std::vector<Guest> expected{guest2};
        REQUIRE( guests == expected );
    }
}
