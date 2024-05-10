#include "catch_amalgamated.hpp"
#include "../src/systems/stay_system.hpp"
#include "../src/utilities/errors.hpp"

TEST_CASE("test StaySystem, simple use")
{
    GuestSystem g_system{};
    Guest guest1{"name1"};
    g_system.add_guest(guest1);
    Guest guest2{"name2"};
    g_system.add_guest(guest2);
    RoomsList rooms_list{};
    rooms_list.add_two_room(237);
    auto room1 = rooms_list.find_by_number(237);
    StaySystem s_system{};
    s_system.bind_guest_system(g_system);
    s_system.bind_room_system(rooms_list);
    jed_utils::datetime start1{2024, 5, 10};
    jed_utils::datetime end1{2024, 5, 14};
    Stay stay1{room1, start1, end1};
    stay1.add_guest(guest1);
    stay1.add_guest(guest2);
    s_system.add_stay(stay1);
    std::vector expected{stay1};
    REQUIRE( s_system.get_stays() == expected );
}

TEST_CASE("test StaySystem, unknown guest")
{
    GuestSystem g_system{};
    Guest guest1{"name1"};
    g_system.add_guest(guest1);
    Guest guest2{"name2"};
    RoomsList rooms_list{};
    rooms_list.add_one_room(237);
    auto room1 = rooms_list.find_by_number(237);
    StaySystem s_system{};
    s_system.bind_guest_system(g_system);
    s_system.bind_room_system(rooms_list);
    jed_utils::datetime start1{2024, 5, 10};
    jed_utils::datetime end1{2024, 5, 14};
    Stay stay1{room1, start1, end1};
    REQUIRE_THROWS_AS( s_system.add_stay(stay1), GuestNotInSystemError ); 
}

TEST_CASE("test StaySystem, unknown room")
{
    GuestSystem g_system{};
    Guest guest1{"name1"};
    g_system.add_guest(guest1);
    Guest guest2{"name2"};
    RoomsList rooms_list{};
    Room room1 {237, 2};
    StaySystem s_system{};
    s_system.bind_guest_system(g_system);
    s_system.bind_room_system(rooms_list);
    jed_utils::datetime start1{2024, 5, 10};
    jed_utils::datetime end1{2024, 5, 14};
    Stay stay1{room1, start1, end1};
    REQUIRE_THROWS_AS( s_system.add_stay(stay1), RoomNotInSystemError ); 
}


TEST_CASE("test StaySystem, overlap")
{
    GuestSystem g_system{};
    Guest guest1{"name1"};
    g_system.add_guest(guest1);
    RoomsList rooms_list{};
    rooms_list.add_one_room(237);
    auto room1 = rooms_list.find_by_number(237);
    StaySystem s_system{};
    s_system.bind_guest_system(g_system);
    s_system.bind_room_system(rooms_list);
    jed_utils::datetime start1{2024, 5, 10};
    jed_utils::datetime end1{2024, 5, 14};
    Stay stay1{room1, start1, end1};
    stay1.add_guest(guest1);
    jed_utils::datetime start2{2024, 5, 13};
    jed_utils::datetime end2{2024, 5, 16};
    Stay stay2{room1, start2, end2};
    stay2.add_guest(guest1);
    s_system.add_stay(stay1);
    REQUIRE_THROWS_AS(s_system.add_stay(stay2), StayOverlapError);
}

TEST_CASE("test StaySystem, remove_stay")
{
    GuestSystem g_system{};
    Guest guest1{"name1"};
    g_system.add_guest(guest1);
    Guest guest2{"name2"};
    g_system.add_guest(guest2);
    RoomsList rooms_list{};
    rooms_list.add_two_room(237);
    auto room1 = rooms_list.find_by_number(237);
    StaySystem s_system{};
    s_system.bind_guest_system(g_system);
    s_system.bind_room_system(rooms_list);
    jed_utils::datetime start1{2024, 5, 10};
    jed_utils::datetime end1{2024, 5, 14};
    Stay stay1{room1, start1, end1};
    stay1.add_guest(guest1);
    stay1.add_guest(guest2);
    s_system.add_stay(stay1);
    s_system.remove_stay(stay1);
    REQUIRE( s_system.get_stays().empty() );
}
