#include "catch_amalgamated.hpp"
#include "../src/tasks/prepare_dish_task.hpp"
#include "../src/utilities/errors.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/systems/task_system.hpp"


TEST_CASE("Test Task")
{
    auto rooms_list = RoomsList{};
    auto g_system = GuestSystem{};
    auto w_system = WorkerSystem{};
    Pay pay{PaycheckMethod::Salary, Amount{3200, 0}};
    Cook cook{"name1", "id1", pay};
    Receptionist receptionist{"name2", "id2", pay};
    auto t_system = TaskSystem{w_system, rooms_list, g_system};
    PrepareDishTask preptask{"1111", Dish::Omelette};
    t_system.add_task(preptask);
    Task& task1 = preptask;

    SECTION("init")
    {
        REQUIRE(task1.get_description() == "Prepare a dish.");
        REQUIRE(task1.get_id() == "1111");
        REQUIRE(task1.get_status() == TaskStatus::unassigned);
    }

    SECTION("completion before assignment")
    {
        REQUIRE_THROWS_AS(task1.mark_completed(), TaskStatusError);
    }

    SECTION("'blind'assignment")
    {
        task1.assign(cook);
        REQUIRE(task1.get_status() == TaskStatus::assigned);
    }

    SECTION("incorrect assignment")
    {
        REQUIRE_THROWS_AS(task1.assign(receptionist), TaskAssignmentError);
    }
}
