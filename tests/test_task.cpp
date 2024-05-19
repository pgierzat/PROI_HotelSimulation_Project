#include "catch_amalgamated.hpp"
#include "../src/tasks/prepare_dish_task.hpp"
#include "../src/utilities/errors.hpp"
#include "../src/workers/receptionist.hpp"


TEST_CASE("Test Task")
{
    PrepareDishTask preptask{"1111", Dish::Omelette};
    Task& task = preptask;

    Pay pay{PaycheckMethod::Salary, Amount{3200, 0}};
    Cook cook{"name1", "id1", pay};
    Receptionist receptionist{"name2", "id2", pay};

    SECTION("init")
    {
        REQUIRE(task.get_description() == "Prepare a dish.");
        REQUIRE(task.get_id() == "1111");
        REQUIRE(task.get_status() == TaskStatus::unassigned);
    }

    SECTION("completion before assignment")
    {
        REQUIRE_THROWS_AS(task.mark_completed(), TaskStatusError);
    }

    SECTION("'blind'assignment")
    {
        task.assign(cook);
        REQUIRE(task.get_status() == TaskStatus::assigned);
    }

    SECTION("incorrect assignment")
    {
        REQUIRE_THROWS_AS(task.assign(receptionist), TaskAssignmentError);
    }
}
