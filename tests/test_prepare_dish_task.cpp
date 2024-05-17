#include "catch_amalgamated.hpp"
#include "../src/tasks/prepare_dish_task.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test PrepareDishTask")
{
    PrepareDishTask preptask{"1111", Dish::Omelette};
    Task& task = preptask;
    Cook cook{"name1", "id1", Pay{PaycheckMethod::Salary, Amount{3100, 0}}};

    SECTION("init")
    {
        REQUIRE(preptask.get_dish() == Dish::Omelette);
    }

    SECTION("assignment")
    {
        preptask.assign(cook);
        REQUIRE(task.get_assignee() == cook);
        REQUIRE(task.get_status() == TaskStatus::assigned);
    }

    SECTION("unassignment")
    {
        preptask.assign(cook);
        task.unassign();
        REQUIRE(task.get_status() == TaskStatus::unassigned);
        REQUIRE_THROWS_AS(task.get_assignee(), TaskStatusError);
    }

    SECTION("assignment of a completed task")
    {
        preptask.assign(cook);
        task.mark_completed();
        REQUIRE_THROWS_AS(preptask.assign(cook), TaskAssignmentError);
    }

    SECTION("completion")
    {
        preptask.assign(cook);
        task.mark_completed();
        REQUIRE(task.get_status() == TaskStatus::completed);
    }
}
