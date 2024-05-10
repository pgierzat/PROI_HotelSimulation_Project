#include "catch_amalgamated.hpp"
#include "../src/systems/guest_system.hpp"

TEST_CASE("test GuestSystem")
{
    GuestSystem g_system{};
    Guest guest1{"name1"};
    Guest guest2{"name2"};
    g_system.add_guest(guest1);
    g_system.add_guest(guest2);
    auto found1 = (g_system.find_by_name("name1")).value();
    REQUIRE( found1.get_name() == "name1" );
    REQUIRE( !g_system.find_by_name("name3").has_value() );
    g_system.remove_guest(guest1);
    std::vector<Guest> expected{guest2};
    REQUIRE( g_system.get_guests() == expected );
}
