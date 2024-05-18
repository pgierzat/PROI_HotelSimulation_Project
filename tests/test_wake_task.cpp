#include "catch_amalgamated.hpp"
#include "../src/tasks/wake_task.hpp"
#include "../src/rooms/hpp/room.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test WakeTask")
{
    Room room{237, 1};
    jed_utils::datetime time{2024, 5, 18, 6, 45};
    WakeTask waketask{"1111", room, time};
    Task& task = waketask;
    Maid maid{"name1", "id1", Pay{PaycheckMethod::Salary, Amount{3100, 0}}};

    SECTION("init")
    {
        REQUIRE(waketask.get_room() == room);
        REQUIRE(waketask.get_time() == time);
    }

    SECTION("assignment")
    {
        waketask.assign(maid);
        REQUIRE(task.get_assignee() == maid);
        REQUIRE(task.get_status() == TaskStatus::assigned);
    }

    SECTION("unassignment")
    {
        waketask.assign(maid);
        task.unassign();
        REQUIRE(task.get_status() == TaskStatus::unassigned);
        REQUIRE_THROWS_AS(task.get_assignee(), TaskStatusError);
    }

    SECTION("assignment of a completed task")
    {
        waketask.assign(maid);
        task.mark_completed();
        REQUIRE_THROWS_AS(waketask.assign(maid), TaskAssignmentError);
    }

    SECTION("completion")
    {
        waketask.assign(maid);
        task.mark_completed();
        REQUIRE(task.get_status() == TaskStatus::completed);
    }
}
