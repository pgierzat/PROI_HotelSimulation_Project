#include "catch_amalgamated.hpp"
#include "../src/tasks/wake_task.hpp"
#include "../src/systems/task_system.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/rooms/hpp/one_room.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test WakeTask")
{
    WorkerSystem w_system{};
    Maid maid{"id1", "name1", Pay{PaycheckMethod::Salary, Amount{3100, 0}}};
    w_system.add_worker(maid);
    RoomsList rooms_list{};
    rooms_list.add_room(OneRoom{"237"});
    const auto& room = rooms_list.get_by_id("237");
    GuestSystem g_system{};
    Guest guest1{"1111", "name1"};
    g_system.add_guest(guest1);
    TaskSystem t_system{w_system, rooms_list, g_system};
    
    jed_utils::datetime time{2024, 5, 18, 6, 45};
    WakeTask waketask{"1111", room, time};
    Task& task = waketask;
    t_system.add_task(waketask);

    SECTION("init")
    {
        REQUIRE(task.get_description() == "Wake guest(s) at a room.");
        REQUIRE(waketask.get_room() == room);
        REQUIRE(waketask.get_time() == time);
    }
}
