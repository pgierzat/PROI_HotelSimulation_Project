#include "catch_amalgamated.hpp"
#include "../src/simulation/systematic_task_generator.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/tasks/room_cleaning_task.hpp"


TEST_CASE("Test SystematicTaskGenerator")
{
    auto g_system = GuestSystem{};
    auto w_system = WorkerSystem{};
    auto rooms_list = RoomsList{};
    rooms_list.add_two_apartment(237);
    rooms_list.add_one_room(238);
    const auto& room1 = rooms_list.get_by_number(237);
    const auto& room2 = rooms_list.get_by_number(238);
    auto t_system = TaskSystem{w_system, rooms_list, g_system};
    auto syst_gen = SystematicTaskGenerator{t_system, rooms_list};
    syst_gen.generate_room_cleaning_tasks();

    SECTION("room cleaning tasks")
    {
        auto task1 = RoomCleaningTask{"1", room1};
        auto task2 = RoomCleaningTask{"2", room2};
        auto expected = std::vector{task1, task2};
        auto tasks = t_system.get_tasks();
        REQUIRE(std::ranges::equal(tasks, expected, [](auto t1, const auto& t2){ return *t1 == t2; }));
    }
}
