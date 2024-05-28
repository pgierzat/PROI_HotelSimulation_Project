#include "catch_amalgamated.hpp"
#include "../src/types/stay.hpp"
#include "../src/systems/stay_system.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test Stay")
{
    auto g_system = GuestSystem{};
    Guest guest1{"id1", "name1"};
    Guest guest2{"id2", "name2"};
    g_system.add_guest(guest1);
    g_system.add_guest(guest2);
    auto rooms_list = RoomsList{};
    rooms_list.add_two_room(237);
    const auto& room1 = rooms_list.get_by_number(237);
    StaySystem s_system{g_system, rooms_list};
    jed_utils::datetime start{2012, 12, 12};
    jed_utils::datetime end{2012, 12, 14};

    SECTION("init")
    {
        jed_utils::datetime start_long{2012, 12, 12, 6, 15, 5};
        jed_utils::datetime end_long{2012, 12, 14, 3, 12, 7};
        Stay stay{"id1", room1, guest1, start_long, end_long};
        stay.add_guest(guest2);
        const auto& guests = stay.get_guests();

        SECTION("regular")
        {
            std::vector<Guest> exp{guest1, guest2};
            REQUIRE( std::ranges::equal(guests, exp, [](auto g1, const auto& g2){ return *g1 == g2; }));
            REQUIRE( stay.get_main_guest() == guest1 );
            REQUIRE( stay.get_room() == room1 );
            REQUIRE( stay.get_start() == jed_utils::datetime{2012, 12, 12} );
            REQUIRE( stay.get_end() == jed_utils::datetime{2012, 12, 14} );
        }

        SECTION("setters")
        {
            jed_utils::datetime nstart{2012, 12, 13};
            jed_utils::datetime nend{2012, 12, 16};
            stay.set_end(nend);
            stay.set_start(nstart);
            stay.set_status(StayStatus::checked_out);
            REQUIRE( stay.get_start() == nstart );
            REQUIRE( stay.get_end() == nend );
            REQUIRE( stay.get_status() == StayStatus::checked_out );
        }

        SECTION("setters, invalid, end before start")
        {
            jed_utils::datetime nstart{2012, 12, 15};
            jed_utils::datetime nend{2012, 12, 11};
            REQUIRE_THROWS( stay.set_start(nstart) );
            REQUIRE_THROWS( stay.set_end(nend) );
        }
    }

    SECTION("invalid init, end before start")
    {
        jed_utils::datetime nstart{2012, 12, 14};
        jed_utils::datetime nend{2012, 12, 12};
        REQUIRE_THROWS( Stay{"id1", room1, guest2, nstart, nend} );
    }

    SECTION("too many guests")
    {
        Stay stay{"id1", room1, guest1, start, end};
        stay.add_guest(guest2);
        Guest guest3{"id3", "name3"};
        REQUIRE_NOTHROW(stay.add_guest(guest3));
    }
}
