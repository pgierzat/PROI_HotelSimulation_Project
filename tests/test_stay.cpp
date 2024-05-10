#include "catch_amalgamated.hpp"
#include "../src/types/stay.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test Stay")
{
    Guest guest1{"name1"};
    Guest guest2{"name2"};
    Room room{237, 2};
    jed_utils::datetime start{2012, 12, 12};
    jed_utils::datetime end{2012, 12, 14};

    SECTION("init")
    {
        jed_utils::datetime start_long{2012, 12, 12, 6, 15, 5};
        jed_utils::datetime end_long{2012, 12, 14, 3, 12, 7};
        Stay stay{room, start_long, end_long};
        stay.add_guest(guest1);
        stay.add_guest(guest2);
        auto guests = stay.get_guests();

        SECTION("regular")
        {
            REQUIRE( *guests.at(0) == guest1 );
            REQUIRE( *guests.at(1) == guest2 );
            REQUIRE( stay.get_room() == room );
            REQUIRE( stay.get_start() == jed_utils::datetime{2012, 12, 12} );
            REQUIRE( stay.get_end() == jed_utils::datetime{2012, 12, 14} );
            REQUIRE( stay.get_interval() == TimeInterval{start, end} );
        }

        SECTION("setters")
        {
            jed_utils::datetime nstart{2012, 12, 13};
            jed_utils::datetime nend{2012, 12, 16};
            stay.set_end(nend);
            stay.set_start(nstart);
            REQUIRE( stay.get_start() == nstart );
            REQUIRE( stay.get_end() == nend );
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
        REQUIRE_THROWS( Stay{room, nstart, nend} );
    }

    SECTION("too many guests")
    {
        Stay stay{room, start, end};
        Guest guest3{"name3"};
        stay.add_guest(guest1); 
        stay.add_guest(guest2); 
        REQUIRE_THROWS_AS(stay.add_guest(guest3), RoomCapacityExceededError);
    }
    
}
