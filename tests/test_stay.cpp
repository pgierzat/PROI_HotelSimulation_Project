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
    auto guest1 = Guest{"id1", "name1"};
    auto guest2 = Guest{"id2", "name2"};
    auto guest3 = Guest{"id3", "name3"};
    auto rooms_list = RoomsList{};
    auto room1 = TwoRoom{"237"};
    jed_utils::datetime start{2012, 12, 12};
    jed_utils::datetime end{2012, 12, 14};
    auto stay = Stay{"id1", room1, guest1, start, end};

    SECTION("init")
    {
        

        SECTION("regular")
        {
            std::vector<const Guest*> exp{&guest1};
            REQUIRE( stay.get_guests() == exp );
            REQUIRE( stay.get_main_guest() == guest1 );
            REQUIRE( stay.get_room() == room1 );
            REQUIRE( stay.get_start() == start );
            REQUIRE( stay.get_end() == end );
            auto interval = stay.get_interval();
            REQUIRE( interval.get_start() == start + Stay::checkin_time);
            REQUIRE( interval.get_end() == end + Stay::checkout_time);
        }

        SECTION("long dates")
        {
            jed_utils::datetime start_long{2012, 12, 12, 6, 15, 5};
            jed_utils::datetime end_long{2012, 12, 14, 3, 12, 7};
            auto stay1 = Stay{"id1", room1, guest1, start_long, end_long};
            REQUIRE( stay.get_start() == start + Stay::checkin_time );
            REQUIRE( stay.get_end() == end + Stay::checkout_time);
        }

        SECTION("setters")
        {
            auto stay2 = Stay{"id2", room1, guest2, start, end};
            jed_utils::datetime nstart{2012, 12, 13, 16};
            jed_utils::datetime nend{2012, 12, 16, 10};
            stay2.set_end(nend);
            stay2.set_start(nstart);
            REQUIRE( stay2.get_start() == nstart );
            REQUIRE( stay2.get_end() == nend );
        }

        SECTION("setting status freely")
        {
            stay.set_status(StayStatus::checked_out);
            REQUIRE( stay.get_status() == StayStatus::checked_out );
            stay.set_status(StayStatus::booked);
            REQUIRE( stay.get_status() == StayStatus::booked );
            stay.set_status(StayStatus::checked_in);
            REQUIRE( stay.get_status() == StayStatus::checked_in );
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
            std::vector<const Guest*> exp_guests{&guest1, &guest2};
            REQUIRE( stay.get_guests() == exp_guests );
        }

        SECTION("duplicate guest")
        {
            REQUIRE_THROWS( stay.add_guest(guest1) );
        }

        SECTION("'na waleta' guest")
        {
            stay.add_guest(guest2);
            REQUIRE_THROWS_AS( stay.add_guest(guest3), RoomCapacityExceededError );
        }
    }
}
