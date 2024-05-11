#include "catch_amalgamated.hpp"
#include "../src/systems/stay_system.hpp"
#include "../src/utilities/errors.hpp"

TEST_CASE("test StaySystem")
{
    GuestSystem g_system{};
    Guest guest1{"name1"};
    Guest guest2{"name2"};
    g_system.add_guest(guest1);
    g_system.add_guest(guest2);
    RoomsList rooms_list{};
    rooms_list.add_two_room(237);
    auto room1 = rooms_list.find_by_number(237);
    StaySystem s_system{};
    s_system.bind_guest_system(g_system);
    s_system.bind_room_system(rooms_list);
    jed_utils::datetime start1{2024, 5, 10};
    jed_utils::datetime end1{2024, 5, 14};
    const auto& stays = s_system.get_stays();

    SECTION("add stay")
    {
        Stay stay1{room1, start1, end1};
        stay1.add_guest(guest1);
        stay1.add_guest(guest2);
        s_system.add_stay(stay1);
        std::vector expected{stay1};
        REQUIRE( stays == expected );
    }

    SECTION("remove stay")
    {
        Stay stay1{room1, start1, end1};
        stay1.add_guest(guest1);
        stay1.add_guest(guest2);
        s_system.add_stay(stay1);
        s_system.remove_stay(stay1);
        REQUIRE( stays.empty() );
    }

    SECTION("no guests")
    {
        Stay stay1{room1, start1, end1};
        REQUIRE_THROWS( s_system.add_stay(stay1) ); 
    }

    SECTION("unknown guest")
    {
        Stay stay1{room1, start1, end1};
        Guest guest3{"name3"};
        stay1.add_guest(guest3);
        REQUIRE_THROWS_AS( s_system.add_stay(stay1), GuestNotInSystemError ); 
    }

    SECTION("unknown room")
    {
        Room room2{238, 1};
        Stay stay1{room2, start1, end1};
        stay1.add_guest(guest1);
        REQUIRE_THROWS_AS( s_system.add_stay(stay1), RoomNotInSystemError ); 
    }

    SECTION("stay overlap")
    {
        Stay stay1{room1, start1, end1};
        stay1.add_guest(guest1);
        jed_utils::datetime start2{2024, 5, 13};
        jed_utils::datetime end2{2024, 5, 16};
        Stay stay2{room1, start2, end2};
        stay2.add_guest(guest1);
        s_system.add_stay(stay1);
        REQUIRE_THROWS_AS(s_system.add_stay(stay2), StayOverlapError);
    }

    SECTION("time test")
    {
        Stay stay1{room1, start1, end1};
        stay1.add_guest(guest1);
        stay1.add_guest(guest2);
        s_system.add_stay(stay1);
        REQUIRE( s_system.get_active_stays().empty() );
        REQUIRE( s_system.get_ending_stays().empty() );
        s_system.set_time(start1);
        REQUIRE( *s_system.get_active_stays().at(0) == stay1 );
        REQUIRE( s_system.get_ending_stays().empty() );
        s_system.set_time(end1 + jed_utils::timespan{1});
        REQUIRE( s_system.get_active_stays().empty() ); 
        REQUIRE( *s_system.get_ending_stays().at(0) == stay1 );
    }
}
