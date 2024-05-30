#include "catch_amalgamated.hpp"
#include "../src/tasks/wake_task.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/systems/stay_system.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/utilities/errors.hpp"

TEST_CASE("test WakeTask")
{
    auto rooms_list = RoomsList{};
    rooms_list.add_one_room(237);
    const auto& room1 = *rooms_list.find_by_number(237).value();
    auto w_system = WorkerSystem{};
    auto pay = Pay{PaycheckMethod::Salary, Amount{3200, 0}};
    w_system.add_worker(Maid{"id1", "name1", pay});
    w_system.add_worker(Maid{"id2", "name2", pay});
    const auto& maid1 = *w_system.find_by_id("id1").value();
    const auto& maid2 = *w_system.find_by_id("id2").value();
    jed_utils::datetime time{2024, 5, 18};
    WakeTask waketask{"id1", room1, time};
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