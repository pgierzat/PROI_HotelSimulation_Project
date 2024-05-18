#include "catch_amalgamated.hpp"
#include "../src/tasks/bring_dish_task.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test BringDishTask")
{
    Table table{"25"};
    BringDishTask bringtask{"1111", Dish::Omelette, table};
    Task& task = bringtask;
    Waiter waiter{"name1", "id1", Pay{PaycheckMethod::Salary, Amount{3100, 0}}};

    SECTION("init")
    {
        REQUIRE(bringtask.get_dish() == Dish::Omelette);
        REQUIRE(bringtask.get_table() == table);
    }

    SECTION("assignment")
    {
        bringtask.assign(waiter);
        REQUIRE(task.get_assignee() == waiter);
        REQUIRE(task.get_status() == TaskStatus::assigned);
    }

    SECTION("unassignment")
    {
        bringtask.assign(waiter);
        task.unassign();
        REQUIRE(task.get_status() == TaskStatus::unassigned);
        REQUIRE_THROWS_AS(task.get_assignee(), TaskStatusError);
    }

    SECTION("assignment of a completed task")
    {
        bringtask.assign(waiter);
        task.mark_completed();
        REQUIRE_THROWS_AS(bringtask.assign(waiter), TaskAssignmentError);
    }

    SECTION("completion")
    {
        bringtask.assign(waiter);
        task.mark_completed();
        REQUIRE(task.get_status() == TaskStatus::completed);
    }
}
