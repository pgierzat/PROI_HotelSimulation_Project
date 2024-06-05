#include "catch_amalgamated.hpp"
#include "../src/types/stay.hpp"
#include "../src/systems/stay_system.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/rooms/hpp/two_room.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test Stay")
{
    auto g_system = GuestSystem{};
    Guest guest1{"id1", "name1"};
    Guest guest2{"id2", "name2"};
    g_system.add_guest(guest1);
    g_system.add_guest(guest2);
    auto rooms_list = RoomsList{};
    rooms_list.add_room(TwoRoom{"237"});
    const auto& room1 = rooms_list.get_by_id("237");
    StaySystem s_system{g_system, rooms_list};
    jed_utils::datetime start{2012, 12, 12};
    jed_utils::datetime end{2012, 12, 14};

    SECTION("init")
    {
        jed_utils::datetime start_long{2012, 12, 12, 6, 15, 5};
        jed_utils::datetime end_long{2012, 12, 14, 3, 12, 7};

        s_system.add_stay(Stay{"id1", room1, guest1, start_long, end_long});
        auto& stay = s_system.get_by_id("id1");
        const auto& guests = stay.get_guests();

        SECTION("regular")
        {
            std::vector<Guest> exp{guest1};
            REQUIRE( std::ranges::equal(guests, exp, [](auto g1, const auto& g2){ return *g1 == g2; }));
            REQUIRE( stay.get_main_guest() == guest1 );
            REQUIRE( stay.get_room() == room1 );
            REQUIRE( stay.get_start() == jed_utils::datetime{2012, 12, 12} );
            REQUIRE( stay.get_end() == jed_utils::datetime{2012, 12, 14} );
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
}
