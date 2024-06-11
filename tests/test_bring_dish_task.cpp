#include "catch_amalgamated.hpp"
#include "../src/tasks/bring_dish_task.hpp"
#include "../src/systems/task_system.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test BringDishTask")
{
    auto rooms_list = RoomsList{};
    auto w_system = WorkerSystem{};
    auto g_system = GuestSystem{};
    auto t_system = TaskSystem{w_system, rooms_list, g_system};
    BringDishTask bringtask{"1111", Dish::Omelette, "25"};
    t_system.add_task(bringtask);
    Task& task = bringtask;

    SECTION("init")
    {
        REQUIRE(task.get_description() == "Bring a dish to a table.");
        REQUIRE(bringtask.get_dish() == Dish::Omelette);
        REQUIRE(bringtask.get_table_nr() == "25");
    }
}
