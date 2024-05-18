#include "catch_amalgamated.hpp"
#include "../src/tasks/wake_task.hpp"
#include "../src/utilities/errors.hpp"

TEST_CASE("test WakeTask")
{
    Room room{237, 2};
    jed_utils::datetime time{2024, 5, 18};
    Maid maid1{"name1", "id1", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
    Maid maid2{"name2", "id2", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
    WakeTask waketask{"id1", room, time};
    Task& task = waketask;

    SECTION("assignee of a unassigned task")
    {
        REQUIRE_THROWS_AS(waketask.get_assignee(), TaskStatusError);
    }
    
    SECTION("unassignment of an unassigned task")
    {
        waketask.unassign();
        REQUIRE_THROWS_AS(waketask.get_assignee(), TaskStatusError);
    }

    SECTION("assignment")
    {
        waketask.assign(maid1);
        REQUIRE(waketask.get_assignee() == maid1);
        REQUIRE(waketask.get_status() == TaskStatus::assigned);
    }

    SECTION("reassignment")
    {
        waketask.assign(maid1);
        waketask.assign(maid2);
        REQUIRE(waketask.get_assignee() == maid2);
        REQUIRE(waketask.get_status() == TaskStatus::assigned);
    }

    SECTION("unassignment")
    {
        waketask.assign(maid1);
        waketask.unassign();
        REQUIRE_THROWS_AS(waketask.get_assignee(), TaskStatusError);
        REQUIRE(waketask.get_status() == TaskStatus::unassigned);
    }

    SECTION("completion")
    {
        waketask.assign(maid1);
        task.mark_completed();
        REQUIRE(waketask.get_status() == TaskStatus::completed);
    }

    SECTION("unassignment after completion")
    {
        waketask.assign(maid1);
        task.mark_completed();
        REQUIRE_THROWS_AS(waketask.unassign(), TaskStatusError);
    }

    SECTION("reassignment after completion")
    {
        waketask.assign(maid1);
        task.mark_completed();
        REQUIRE_THROWS_AS(waketask.assign(maid2), TaskAssignmentError);
    }
}