#include "catch_amalgamated.hpp"
#include "../src/systems/clock.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/systems/stay_system.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/rooms/hpp/two_room.hpp"
#include "../src/rooms/hpp/one_room.hpp"
#include "../src/utilities/errors.hpp"
#include "../src/functions/equal_operators.hpp"

TEST_CASE("test StaySystem")
{
    auto ck = Clock{};
    auto g_system = GuestSystem{};
    g_system.add_guest(Guest{"id1", "name1"});
    g_system.add_guest(Guest{"id2", "name2"});
    g_system.add_guest(Guest{"id3", "name3"});
    auto& guest1 = g_system.get_by_id("id1");
    auto& guest2 = g_system.get_by_id("id2");
    auto& guest3 = g_system.get_by_id("id3");
    RoomsList rooms_list{};
    rooms_list.add_room(TwoRoom{"237"});
    rooms_list.add_room(OneRoom{"217"});
    const auto& room1 = rooms_list.get_by_id("237");
    const auto& room2 = rooms_list.get_by_id("217");
    StaySystem s_system{ck, g_system, rooms_list};
    jed_utils::datetime start1{2024, 5, 10};
    jed_utils::datetime end1{2024, 5, 14};
    jed_utils::datetime start2{2024, 5, 14};
    jed_utils::datetime end2{2024, 5, 16};
    jed_utils::datetime start3{2024, 5, 18};
    jed_utils::datetime end3{2024, 5, 21};
    auto stay1_temp = Stay{"id1", room1, guest1, start1, end1};
    stay1_temp.add_guest(guest2);
    s_system.add_stay(stay1_temp);
    s_system.add_stay(Stay{"id2", room2, guest3, start2, end2});
    const auto& stay1 = s_system.get_by_id("id1");
    const auto& stay2 = s_system.get_by_id("id2");

    SECTION("add stay")
    {
        auto stays = s_system.get_stays();
        std::vector<const Stay*> expected{&stay1, &stay2};
        REQUIRE( stays == expected );
    }

    SECTION("remove stay")
    {
        s_system.remove_stay(stay1);
        std::vector<const Stay*> expected{&stay2};
        REQUIRE( s_system.get_stays() == expected );
    }

    SECTION("status not 'booked'")
    {
        Stay stay3{"id1", room1, guest1, start1, end1};
        stay3.set_status(StayStatus::checked_in);
        REQUIRE_THROWS( s_system.add_stay(stay3) ); 
        stay3.set_status(StayStatus::checked_out);
        REQUIRE_THROWS( s_system.add_stay(stay3) ); 
    }

    SECTION("unknown guest")
    {
        Guest guest4{"id4", "name4"};
        Stay stay3{"id3", room2, guest4, start1, end1};
        REQUIRE_THROWS_AS( s_system.add_stay(stay3), GuestNotInSystemError ); 
        auto stays = s_system.get_stays();      // and make sure it hasn't been added
        std::vector<const Stay*> expected{&stay1, &stay2};
        REQUIRE( stays == expected );
    }

    SECTION("unknown room")
    {
        Room room3{"238", 1};
        Stay stay3{"id1", room3, guest1, start1, end1};
        REQUIRE_THROWS_AS( s_system.add_stay(stay3), RoomNotInSystemError ); 
        auto stays = s_system.get_stays();
        std::vector<const Stay*> expected{&stay1, &stay2};
        REQUIRE( stays == expected );
    }

    SECTION("stay overlap")
    {
        jed_utils::datetime start4{2024, 5, 13};
        jed_utils::datetime end4{2024, 5, 16};
        Stay stay3{"id3", room1, guest2, start4, end4};
        REQUIRE_THROWS_AS(s_system.add_stay(stay3), StayOverlapError);
        auto stays = s_system.get_stays();
        std::vector<const Stay*> expected{&stay1, &stay2};
        REQUIRE( stays == expected );
    }

    SECTION("check-in and check-out")
    {
        jed_utils::datetime before{2024, 5, 10, 6};
        jed_utils::datetime during1{2024, 5, 12};
        jed_utils::datetime during2{2024, 5, 13};
        jed_utils::datetime during3{2024, 5, 14, 9, 30};
        jed_utils::datetime after{2024, 5, 14, 15};

        SECTION("check-in")
        {
            ck.set_time(during1);
            s_system.check_in(stay1);
            REQUIRE(stay1.get_status() == StayStatus::checked_in);
        }

        SECTION("double check-in")
        {
            ck.set_time(during1);
            s_system.check_in(stay1);
            ck.set_time(during2);
            s_system.check_in(stay1);
            REQUIRE(stay1.get_status() == StayStatus::checked_in);
        }

        SECTION("check-in before and after")
        {
            ck.set_time(before);
            REQUIRE_THROWS_AS(s_system.check_in(stay1), StayStatusError);
            ck.set_time(after);
            REQUIRE_THROWS_AS(s_system.check_in(stay1), StayStatusError);
        }

        SECTION("check-out")
        {
            ck.set_time(during1);
            s_system.check_in(stay1);
            ck.set_time(during2);
            s_system.check_out(stay1);
            REQUIRE(stay1.get_status() == StayStatus::checked_out);
        }

        SECTION("double check-out")
        {
            ck.set_time(during1);
            s_system.check_in(stay1);
            ck.set_time(during2);
            s_system.check_out(stay1);
            ck.set_time(during3);
            s_system.check_out(stay1);
            REQUIRE(stay1.get_status() == StayStatus::checked_out);
        }

        SECTION("check-in after check-out")
        {
            ck.set_time(during1);
            s_system.check_in(stay1);
            ck.set_time(during2);
            s_system.check_out(stay1);
            REQUIRE_THROWS_AS(s_system.check_in(stay1), StayStatusError);
        }

        SECTION("check-out before check-in")
        {
            ck.set_time(during1);
            REQUIRE_THROWS_AS(s_system.check_out(stay1), StayStatusError);
        }
    }

    SECTION("Observer tests")
    {
        SECTION("remove guest")
        {
            g_system.remove_guest(guest2);
            auto stays = s_system.get_stays();
            std::vector<const Stay*> expected{&stay2};      // stay1 had guest2 among its guests
            REQUIRE( stays == expected );
        }
    }
}
