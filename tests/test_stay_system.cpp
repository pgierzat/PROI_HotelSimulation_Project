#include "catch_amalgamated.hpp"
#include "../src/systems/stay_system.hpp"
#include "../src/utilities/errors.hpp"

TEST_CASE("test StaySystem")
{
    GuestSystem g_system{};
    Guest guest1{"id1", "name1"};
    Guest guest2{"id2", "name2"};
    g_system.add_guest(guest1);
    g_system.add_guest(guest2);
    RoomsList rooms_list{};
    rooms_list.add_two_room(237);
    rooms_list.add_one_room(217);
    const auto& room1 = *rooms_list.find_by_number(237).value();
    const auto& room2 = *rooms_list.find_by_number(217).value();
    StaySystem s_system{g_system, rooms_list};
    jed_utils::datetime start1{2024, 5, 10};
    jed_utils::datetime end1{2024, 5, 14};
    jed_utils::datetime start2{2024, 5, 14};
    jed_utils::datetime end2{2024, 5, 16};
    const auto& stays = s_system.get_stays();

    SECTION("add stay")
    {
        Stay stay1{"id1", room1, guest1, start1, end1};
        stay1.add_guest(guest2);
        s_system.add_stay(stay1);
        std::vector expected{stay1};
        REQUIRE( stays == expected );
    }

    SECTION("remove stay")
    {
        Stay stay1{"id1", room1, guest1, start1, end1};
        stay1.add_guest(guest2);
        s_system.add_stay(stay1);
        Stay stay2{"id2", room2, guest2, start2, end2};
        s_system.add_stay(stay2);
        s_system.remove_stay(stay1);
        std::vector expected{stay2};
        REQUIRE( stays == expected );
    }

    SECTION("status not 'booked'")
    {
        Stay stay1{"id1", room1, guest1, start1, end1};
        stay1.set_status(StayStatus::checked_in);
        REQUIRE_THROWS( s_system.add_stay(stay1) ); 
        stay1.set_status(StayStatus::checked_out);
        REQUIRE_THROWS( s_system.add_stay(stay1) ); 
    }

    SECTION("unknown guest")
    {
        Guest guest3{"id3", "name3"};
        Stay stay1{"id1", room1, guest3, start1, end1};
        REQUIRE_THROWS_AS( s_system.add_stay(stay1), GuestNotInSystemError ); 
    }

    SECTION("unknown room")
    {
        Room room3{238, 1};
        Stay stay1{"id1", room3, guest1, start1, end1};
        REQUIRE_THROWS_AS( s_system.add_stay(stay1), RoomNotInSystemError ); 
    }

    SECTION("stay overlap")
    {
        Stay stay1{"id1", room1, guest1, start1, end1};
        jed_utils::datetime start3{2024, 5, 13};
        jed_utils::datetime end3{2024, 5, 16};
        Stay stay2{"id2", room1, guest2, start3, end3};
        s_system.add_stay(stay1);
        REQUIRE_THROWS_AS(s_system.add_stay(stay2), StayOverlapError);
    }

    SECTION("stay interval")
    {
        Stay stay1{"id1", room1, guest1, start1, end1};
        auto interval = stay1.get_interval();
        REQUIRE( interval.get_start() == start1 + StaySystem::checkin_time);
        REQUIRE( interval.get_end() == end1 + StaySystem::checkout_time);
    }

    SECTION("check-in and check-out")
    {
        Stay stay1{"id1", room1, guest1, start1, end1};
        jed_utils::datetime before{2024, 5, 10, 6};
        jed_utils::datetime during1{2024, 5, 12};
        jed_utils::datetime during2{2024, 5, 13};
        jed_utils::datetime during3{2024, 5, 14, 9, 30};
        jed_utils::datetime after{2024, 5, 14, 15};
        s_system.add_stay(stay1);
        const Stay& stay1ref = *s_system.find_by_id(stay1.get_id()).value();

        SECTION("check-in")
        {
            s_system.set_time(during1);
            s_system.check_in(stay1ref);
            REQUIRE(stay1ref.get_status() == StayStatus::checked_in);
        }

        SECTION("double check-in")
        {
            s_system.set_time(during1);
            s_system.check_in(stay1ref);
            s_system.set_time(during2);
            s_system.check_in(stay1ref);
            REQUIRE(stay1ref.get_status() == StayStatus::checked_in);
        }

        SECTION("check-in before and after")
        {
            s_system.set_time(before);
            REQUIRE_THROWS_AS(s_system.check_in(stay1ref), StayStatusError);
            s_system.set_time(after);
            REQUIRE_THROWS_AS(s_system.check_in(stay1ref), StayStatusError);
        }

        SECTION("check-out")
        {
            s_system.set_time(during1);
            s_system.check_in(stay1ref);
            s_system.set_time(during2);
            s_system.check_out(stay1ref);
            REQUIRE(stay1ref.get_status() == StayStatus::checked_out);
        }

        SECTION("double check-out")
        {
            s_system.set_time(during1);
            s_system.check_in(stay1ref);
            s_system.set_time(during2);
            s_system.check_out(stay1ref);
            s_system.set_time(during3);
            s_system.check_out(stay1ref);
            REQUIRE(stay1ref.get_status() == StayStatus::checked_out);
        }

        SECTION("check-in after check-out")
        {
            s_system.set_time(during1);
            s_system.check_in(stay1ref);
            s_system.set_time(during2);
            s_system.check_out(stay1ref);
            REQUIRE_THROWS_AS(s_system.check_in(stay1ref), StayStatusError);
        }

        SECTION("check-out before check-in")
        {
            s_system.set_time(during1);
            REQUIRE_THROWS_AS(s_system.check_out(stay1ref), StayStatusError);
        }
    }
}
