#include "catch_amalgamated.hpp"
#include "../src/tasks/room_cleaning_task.hpp"
#include "../src/rooms/hpp/two_apartment.hpp"
#include "../src/utilities/errors.hpp"

TEST_CASE("test BigTask")
{
    TwoApartment room{237};
    jed_utils::datetime time{2024, 5, 18};
    Pay pay{PaycheckMethod::Salary, Amount{3200, 0}};
    Maid maid1{"name1", "id1", pay};
    Maid maid2{"name2", "id2", pay};
    Maid maid3{"name2", "id2", pay};
    RoomCleaningTask roomtask{"id1", room};
    Task& task = roomtask;
    const auto& assignees = roomtask.get_assignees();

    SECTION("init")
    {
        REQUIRE(roomtask.get_required() == room.calculatePersonel());
        REQUIRE(assignees.empty());
    }
    
    SECTION("unassignment of an unassigned task")
    {
        roomtask.unassign();
        REQUIRE(assignees.empty());
    }

    SECTION("partial assignment")
    {
        roomtask.assign(maid1);
        std::vector<const Maid*> exp{&maid1};
        REQUIRE(assignees == exp);
        REQUIRE(roomtask.get_status() == TaskStatus::unassigned); // !!!
    }

    SECTION("full assignment")
    {
        roomtask.assign(maid1);
        roomtask.assign(maid2);
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
