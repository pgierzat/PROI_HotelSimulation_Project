#include "catch_amalgamated.hpp"
#include "../src/tasks/room_cleaning_task.hpp"
#include "../src/rooms/hpp/four_apartment.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test RoomCleaningTask")
{
    FourApartment room{237};
    RoomCleaningTask roomtask{"1111", room};
    BigTask& bigtask = roomtask;
    Task& task = roomtask;
    const auto& assignees = roomtask.get_assignees();

    auto pay = Pay{PaycheckMethod::Salary, Amount{3200, 0}};
    Maid maid1{"name1", "1111", pay};
    Maid maid2{"name2", "2222", pay};
    Maid maid3{"name3", "3333", pay};
    Maid maid4{"name4", "4444", pay};


    SECTION("init")
    {
        REQUIRE(bigtask.get_description() == "Clean a room.");
        REQUIRE(bigtask.get_workers().empty());
        REQUIRE(bigtask.get_required() == room.calculatePersonel());
        REQUIRE(bigtask.get_assigned() == 0);
    }

    SECTION("unassignment of an unassigned task")
    {
        task.unassign();
        REQUIRE(task.get_status() == TaskStatus::unassigned);
    }

    SECTION("assignment")
    {
        roomtask.assign(maid1);
        std::vector<const Worker*> expected_workers{&maid1};
        REQUIRE(bigtask.get_workers() == expected_workers);
        std::vector<const Maid*> expected_maids{&maid1};
        REQUIRE(assignees == expected_maids);
        REQUIRE(bigtask.get_assigned() == 1);
        REQUIRE(task.get_status() == TaskStatus::unassigned); // !!!
    }

    SECTION("overassignment")
    {
        roomtask.assign(maid1);
        roomtask.assign(maid2);
        roomtask.assign(maid3);
        REQUIRE_THROWS_AS(roomtask.assign(maid4), TaskCapacityError);
    }

    SECTION("duplicate assignment")
    {
        roomtask.assign(maid1);
        REQUIRE_THROWS_AS(roomtask.assign(maid1), DuplicateWorkerIDError);
    }

    SECTION("unassignment")
    {
        roomtask.assign(maid1);
        roomtask.assign(maid2);
        roomtask.assign(maid3);
        task.unassign();
        REQUIRE(bigtask.get_workers().empty());
        REQUIRE(assignees.empty());
        REQUIRE(task.get_status() == TaskStatus::unassigned);
    }

    SECTION("completion")
    {
        roomtask.assign(maid1);
        roomtask.assign(maid2);
        roomtask.assign(maid3);
        task.mark_completed();
        REQUIRE(task.get_status() == TaskStatus::completed);
    }

    SECTION("assignment of a completed task")
    {
        roomtask.assign(maid1);
        roomtask.assign(maid2);
        roomtask.assign(maid3);
        task.mark_completed();
        REQUIRE_THROWS_AS(roomtask.assign(maid4), TaskAssignmentError);
    }
}
