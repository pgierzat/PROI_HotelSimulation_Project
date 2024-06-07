#include "catch_amalgamated.hpp"
#include "../src/types/stay.hpp"
#include "../src/systems/stay_system.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/rooms/hpp/two_room.hpp"
#include "../src/utilities/errors.hpp"
#include "../src/functions/equal_operators.hpp"


TEST_CASE("Test Stay")
{
    auto g_system = GuestSystem{};
    g_system.add_guest(Guest{"id1", "name1"});
    g_system.add_guest(Guest{"id2", "name2"});
    g_system.add_guest(Guest{"id3", "name3"});
    auto& guest1 = g_system.get_by_id("id1");
    auto& guest2 = g_system.get_by_id("id2");
    auto& guest3 = g_system.get_by_id("id3");
    auto rooms_list = RoomsList{};
    rooms_list.add_room(TwoRoom{"237"});
    const auto& room1 = rooms_list.get_by_id("237");
    jed_utils::datetime start{2012, 12, 12};
    jed_utils::datetime end{2012, 12, 14};
    auto stay = Stay{"id1", room1, guest1, start, end};

    SECTION("init")
    {
        jed_utils::datetime start_long{2012, 12, 12, 6, 15, 5};
        jed_utils::datetime end_long{2012, 12, 14, 3, 12, 7};

        SECTION("regular")
        {
            std::vector<Guest> exp{guest1};
            REQUIRE( stay.get_guests() == exp );
            REQUIRE( stay.get_main_guest() == guest1 );
            REQUIRE( stay.get_room() == room1 );
            REQUIRE( stay.get_start() == jed_utils::datetime{2012, 12, 12} );
            REQUIRE( stay.get_end() == jed_utils::datetime{2012, 12, 14} );
            auto interval = stay.get_interval();
            REQUIRE( interval.get_start() == start + Stay::checkin_time);
            REQUIRE( interval.get_end() == end + Stay::checkout_time);
        }

        SECTION("setters")
        {
            auto stay2 = Stay{"id2", room1, guest2, start, end};
            jed_utils::datetime nstart{2012, 12, 13};
            jed_utils::datetime nend{2012, 12, 16};
            stay2.set_end(nend);
            stay2.set_start(nstart);
            stay2.set_status(StayStatus::checked_out);
            REQUIRE( stay2.get_start() == nstart );
            REQUIRE( stay2.get_end() == nend );
            REQUIRE( stay2.get_status() == StayStatus::checked_out );
        }

        SECTION("setters, invalid, end before start")
        {
            auto stay2 = Stay{"id2", room1, guest2, start, end};
            jed_utils::datetime nstart{2012, 12, 15};
            jed_utils::datetime nend{2012, 12, 11};
            REQUIRE_THROWS( stay2.set_start(nstart) );
            REQUIRE_THROWS( stay2.set_end(nend) );
        }
    }

    SECTION("invalid init, end before start")
    {
        jed_utils::datetime nstart{2012, 12, 14};
        jed_utils::datetime nend{2012, 12, 12};
        REQUIRE_THROWS( Stay{"id2", room1, guest2, nstart, nend} );
    }

    SECTION("adding guests")
    {
        SECTION("regular")
        {
            stay.add_guest(guest2);
            std::vector exp_guests{guest1, guest2};
            REQUIRE( stay.get_guests() == exp_guests );
            std::vector<std::string> exp_guests_ids{"id1", "id2"};
            REQUIRE( stay.get_guest_ids() == exp_guests_ids );
        }

        SECTION("duplicate guest")
        {
            REQUIRE_THROWS( stay.add_guest(guest1) );
        }

        SECTION("unknown guest")
        {
            auto guest4 = Guest{"id4", "name4"};
            REQUIRE_NOTHROW( stay.add_guest(guest4) );
        }

        SECTION("'na waleta' guest")
        {
            stay.add_guest(guest2);
            REQUIRE_THROWS_AS( stay.add_guest(guest3), RoomCapacityExceededError );
        }
    }
}
