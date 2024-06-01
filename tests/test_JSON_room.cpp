#include "catch_amalgamated.hpp"
#include "../src/JSON_converters/JSON_room.hpp"
#include "../src/rooms/hpp/three_room.hpp"
#include "../src/rooms/hpp/two_room.hpp"


TEST_CASE("Test JSONRoom")
{
    SECTION("correct use of read specific")
    {
        auto room = TwoRoom{237};
        auto j = JSONRoom::write(room);
        auto read_room = JSONRoom::read_specific<TwoRoom>(j);
        REQUIRE( room == read_room );
    }

    SECTION("mistaken room type")
    {
        auto room = TwoRoom{237};
        auto j = JSONRoom::write(room);
        REQUIRE_THROWS_AS( JSONRoom::read_specific<ThreeRoom>(j), IncorrectRoomType );
    }

    SECTION("read, unspecific")
    {
        auto room = TwoRoom{237};
        auto j = JSONRoom::write(room);
        auto ptr = JSONRoom::read(j);
        auto read_room = dynamic_cast<TwoRoom&>(*ptr);
        REQUIRE( room == read_room );
    }
}
