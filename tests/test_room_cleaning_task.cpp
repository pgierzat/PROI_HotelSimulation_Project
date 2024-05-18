#include "catch_amalgamated.hpp"
#include "../src/tasks/room_cleaning_task.hpp"
#include "../src/rooms/hpp/four_apartment.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test RoomCleaningTask")
{
    FourApartment room{237};
    RoomCleaningTask roomtask{"1111", room};
    Task& task = roomtask;

    auto pay = Pay{PaycheckMethod::Salary, Amount{3200, 0}};
    Maid maid1{"name1", "1111", pay};
    Maid maid2{"name2", "2222", pay};
    Maid maid3{"name3", "3333", pay};
    Maid maid4{"name4", "4444", pay};


    SECTION("init")
    {
        REQUIRE(task.get_description() == "Clean a room.");
        REQUIRE(roomtask.get_required() == room.calculatePersonel());
    }
}
