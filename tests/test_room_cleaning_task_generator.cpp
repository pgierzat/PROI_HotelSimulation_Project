#include "catch_amalgamated.hpp"
#include "../src/simulation/room_cleaning_task_generator.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/rooms/hpp/one_room.hpp"
#include "../src/rooms/hpp/two_appartment.hpp"
#include "../src/tasks/room_cleaning_task.hpp"


TEST_CASE("Test RoomCleaningTaskGenerator")
{
    auto g_system = GuestSystem{};
    auto w_system = WorkerSystem{};
    auto rooms_list = RoomsList{};
    rooms_list.add_room(TwoAppartment{"237"});
    rooms_list.add_room(OneRoom{"238"});
    const auto& room1 = rooms_list.get_by_id("237");
    const auto& room2 = rooms_list.get_by_id("238");
    auto t_system = TaskSystem{w_system, rooms_list, g_system};
    jed_utils::datetime time0{2024, 5, 19};
    auto gen = RoomCleaningTaskGenerator{t_system, rooms_list, time0};

    SECTION("time test")
    {
        jed_utils::datetime time1{2024, 5, 19, 7};
        gen.set_time(time1);
        REQUIRE(t_system.get_tasks().empty());
        jed_utils::datetime time2{2024, 5, 19, 8};
        gen.set_time(time2);
        auto task1 = RoomCleaningTask{"1", room1};
        auto task2 = RoomCleaningTask{"2", room2};
        auto expected = std::vector{task1, task2};
        auto tasks = t_system.get_tasks();
        REQUIRE(std::ranges::equal(tasks, expected, [](auto t1, const auto& t2){ return *t1 == t2; }));
    }
}
