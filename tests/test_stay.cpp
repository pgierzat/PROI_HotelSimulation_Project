#include "catch_amalgamated.hpp"
#include "../src/types/stay.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test Stay init")
{
    Guest guest1{"name1"};
    Guest guest2{"name2"};
    Room room{237, 2};
    jed_utils::datetime start{2012, 12, 12, 6, 15, 5};
    jed_utils::datetime end{2012, 12, 14, 3, 12, 7};
    Stay stay{room, start, end};
    stay.add_guest(guest1);
    stay.add_guest(guest2);
    std::vector expected{guest1, guest2};
    REQUIRE( stay.get_guests() == expected );
    REQUIRE( stay.get_room() == room );
    REQUIRE( stay.get_start() == jed_utils::datetime{2012, 12, 12} );
    REQUIRE( stay.get_end() == jed_utils::datetime{2012, 12, 14} );
}

TEST_CASE("Test Stay init invalid, end b4 start")
{
    Room room{237, 2};
    jed_utils::datetime start{2012, 12, 14};
    jed_utils::datetime end{2012, 12, 12};
    REQUIRE_THROWS( Stay{room, start, end} );
}

TEST_CASE("Test Stay, too many guests")
{
    Room room{237, 1};
    Guest guest1{"name1"};
    Guest guest2{"name2"};
    jed_utils::datetime start{2012, 12, 12};
    jed_utils::datetime end{2012, 12, 14};
    Stay stay{room, start, end};
    stay.add_guest(guest1);
    REQUIRE_THROWS_AS(stay.add_guest(guest2), RoomCapacityExceededError);
}

TEST_CASE("Test Stay setters")
{
    Guest guest{"name1"};
    Room room{237, 2};
    jed_utils::datetime start{2012, 12, 12};
    jed_utils::datetime end{2012, 12, 14};
    Stay stay{room, start, end};
    jed_utils::datetime nstart{2012, 12, 13};
    jed_utils::datetime nend{2012, 12, 16};
    stay.set_end(nend);
    stay.set_start(nstart);
    REQUIRE( stay.get_start() == nstart );
    REQUIRE( stay.get_end() == nend );
}

TEST_CASE("Test Stay setters invalid")
{
    Guest guest{"name1"};
    Room room{237, 2};
    jed_utils::datetime start{2012, 12, 12};
    jed_utils::datetime end{2012, 12, 14};
    Stay stay{room, start, end};
    jed_utils::datetime nstart{2012, 12, 15};
    jed_utils::datetime nend{2012, 12, 11};
    REQUIRE_THROWS( stay.set_start(nstart) );
    REQUIRE_THROWS( stay.set_end(nend) );
}
