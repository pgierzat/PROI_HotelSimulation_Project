#include "catch_amalgamated.hpp"
#include "../src/tasks/taxi_task.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test TaxiTask")
{
    Guest guest{"name1"};
    jed_utils::datetime time{2024, 5, 18, 6, 45};
    TaxiTask taxitask{"1111", guest, time};
    Task& task = taxitask;
    Receptionist cook{"name2", "id2", Pay{PaycheckMethod::Salary, Amount{3100, 0}}};

    SECTION("init")
    {
        REQUIRE(taxitask.get_guest() == guest);
        REQUIRE(taxitask.get_time() == time);
    }

    SECTION("assignment")
    {
        taxitask.assign(cook);
        REQUIRE(task.get_assignee() == cook);
        REQUIRE(task.get_status() == TaskStatus::assigned);
    }

    SECTION("unassignment")
    {
        taxitask.assign(cook);
        task.unassign();
        REQUIRE(task.get_status() == TaskStatus::unassigned);
        REQUIRE_THROWS_AS(task.get_assignee(), TaskStatusError);
    }

    SECTION("assignment of a completed task")
    {
        taxitask.assign(cook);
        task.mark_completed();
        REQUIRE_THROWS_AS(taxitask.assign(cook), TaskAssignmentError);
    }

    SECTION("completion")
    {
        taxitask.assign(cook);
        task.mark_completed();
        REQUIRE(task.get_status() == TaskStatus::completed);
    }
}
