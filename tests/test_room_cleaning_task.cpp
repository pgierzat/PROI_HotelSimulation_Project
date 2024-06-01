#include "catch_amalgamated.hpp"
#include "../src/tasks/room_cleaning_task.hpp"
#include "../src/rooms/hpp/four_appartment.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test RoomCleaningTask")
{
    auto rooms_list = RoomsList{};
    rooms_list.add_four_appartment(237);
    const auto& room1 = *rooms_list.find_by_number(237).value();
    auto w_system = WorkerSystem{};
    auto pay = Pay{PaycheckMethod::Salary, Amount{3200, 0}};
    Maid maid1{"id1", "name1", pay};
    Maid maid2{"id2", "name2", pay};
    Maid maid3{"id3", "name3", pay};
    Maid maid4{"id4", "name4", pay};
    w_system.add_worker(maid1);
    w_system.add_worker(maid2);
    w_system.add_worker(maid3);
    w_system.add_worker(maid4);
    auto g_system = GuestSystem{};
    Guest guest1{"id1", "name1"};
    g_system.add_guest(guest1);
    auto t_system = TaskSystem{w_system, rooms_list, g_system};
    RoomCleaningTask roomtask{"1111", room1};
    Task& task = roomtask;
    t_system.add_task(roomtask);

    SECTION("init")
    {
        REQUIRE(task.get_description() == "Clean a room.");
        REQUIRE(roomtask.get_required() == room1.calculatePersonel());
    }
}
