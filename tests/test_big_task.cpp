#include "catch_amalgamated.hpp"
#include "../src/tasks/room_cleaning_task.hpp"
#include "../src/rooms/hpp/four_apartment.hpp"


TEST_CASE("Test BigTask")
{
    FourApartment room{237};
    RoomCleaningTask roomtask{"1111", room};
    BigTask& bigtask = roomtask;

    SECTION("init")
    {
        REQUIRE(bigtask.get_required() == room.calculatePersonel());
        REQUIRE(bigtask.get_assigned() == 0);
    }
}