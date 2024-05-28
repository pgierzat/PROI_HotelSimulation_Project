#include "catch_amalgamated.hpp"
#include "../src/tasks/room_cleaning_task.hpp"
#include "../src/rooms/hpp/two_apartment.hpp"
#include "../src/utilities/errors.hpp"
#include "../src/types/datetime.h"

TEST_CASE("test BigTask")
{
    auto rooms_list = RoomsList{};
    rooms_list.add_two_apartment(237);
    const auto& room1 = rooms_list.get_by_number(237);
    jed_utils::datetime time{2024, 5, 18};
    Pay pay{PaycheckMethod::Salary, Amount{3200, 0}};
    auto w_system = WorkerSystem{};
    w_system.add_worker(Maid{"name1", "id1", pay});
    w_system.add_worker(Maid{"name2", "id2", pay});
    w_system.add_worker(Maid{"name3", "id3", pay});
    const auto& maid1 = static_cast<const Maid&>( w_system.get_by_id("id1") );
    const auto& maid2 = static_cast<const Maid&>( w_system.get_by_id("id2") );
    const auto& maid3 = static_cast<const Maid&>( w_system.get_by_id("id3") );
    auto g_system = GuestSystem{};
    auto t_system = TaskSystem{w_system ,rooms_list, g_system};
    RoomCleaningTask roomtask{"id1", room1};
    Task& task = roomtask;

    SECTION("init")
    {
        REQUIRE(roomtask.get_required() == room1.calculatePersonel());
        auto assignees = roomtask.get_assignees();
        REQUIRE(assignees.empty());
    }
    
    SECTION("unassignment of an unassigned task")
    {
        roomtask.unassign();
        auto assignees = roomtask.get_assignees();
        REQUIRE(assignees.empty());
    }

    SECTION("partial assignment")
    {
        roomtask.assign(maid1);
        auto assignees = roomtask.get_assignees();
        std::vector<const Maid*> exp{&maid1};
        REQUIRE(assignees == exp);
        REQUIRE(roomtask.get_status() == TaskStatus::unassigned); // !!!
    }

    SECTION("full assignment")
    {
        roomtask.assign(maid1);
        roomtask.assign(maid2);
        auto assignees = roomtask.get_assignees();
        std::vector<const Maid*> exp{&maid1, &maid2};
        REQUIRE(assignees == exp);
        REQUIRE(roomtask.get_status() == TaskStatus::assigned);
    }

    SECTION("overassignment")
    {
        roomtask.assign(maid1);
        roomtask.assign(maid2);
        REQUIRE_THROWS_AS(roomtask.assign(maid3), TaskCapacityError);
    }

    SECTION("unassignement")
    {
        roomtask.assign(maid1);
        roomtask.assign(maid2);
        roomtask.unassign();
        auto assignees = roomtask.get_assignees();
        REQUIRE(assignees.empty());
        REQUIRE(roomtask.get_status() == TaskStatus::unassigned);
    }

    SECTION("completion")
    {
        roomtask.assign(maid1);
        roomtask.assign(maid2);
        task.mark_completed();
        REQUIRE(roomtask.get_status() == TaskStatus::completed);
    }

    SECTION("unassignment after completion")
    {
        roomtask.assign(maid1);
        roomtask.assign(maid2);
        task.mark_completed();
        REQUIRE_THROWS_AS(roomtask.unassign(), TaskStatusError);
    }

    SECTION("assignment after completion")
    {
        roomtask.assign(maid1);
        roomtask.assign(maid2);
        task.mark_completed();
        REQUIRE_THROWS_AS(roomtask.assign(maid2), TaskAssignmentError);
    }
}
