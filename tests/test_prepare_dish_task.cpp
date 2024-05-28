#include "catch_amalgamated.hpp"
#include "../src/tasks/prepare_dish_task.hpp"
#include "../src/systems/task_system.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test PrepareDishTask")
{
    auto w_system = WorkerSystem{};
    auto rooms_list = RoomsList{};
    auto g_system = GuestSystem{};
    auto t_system = TaskSystem{w_system, rooms_list, g_system};
    PrepareDishTask preptask{"1111", Dish::Omelette};
    t_system.add_task(preptask);
    Task& task = preptask;

    SECTION("init")
    {
        REQUIRE(task.get_description() == "Prepare a dish.");
        REQUIRE(preptask.get_dish() == Dish::Omelette);
    }
}
