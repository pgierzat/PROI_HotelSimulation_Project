#include "catch_amalgamated.hpp"
#include "../src/tasks/wake_task.hpp"
#include "../src/rooms/hpp/room.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test WakeTask")
{
    Room room{237, 1};
    jed_utils::datetime time{2024, 5, 18, 6, 45};
    WakeTask waketask{"1111", room, time};
    Task& task = waketask;
    Maid maid{"name1", "id1", Pay{PaycheckMethod::Salary, Amount{3100, 0}}};

    SECTION("init")
    {
        REQUIRE(task.get_description() == "Wake guest(s) at a room.");
        REQUIRE(waketask.get_room() == room);
        REQUIRE(waketask.get_time() == time);
    }
}
