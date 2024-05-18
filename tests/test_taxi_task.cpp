#include "catch_amalgamated.hpp"
#include "../src/tasks/taxi_task.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test TaxiTask")
{
    Guest guest{"name1"};
    jed_utils::datetime time{2024, 5, 18, 6, 45};
    TaxiTask taxitask{"1111", guest, time};
    SmallTask& smalltask = taxitask;
    Task& task = taxitask;
    Receptionist cook{"name2", "id2", Pay{PaycheckMethod::Salary, Amount{3100, 0}}};

    SECTION("init")
    {
        REQUIRE(taxitask.get_guest() == guest);
        REQUIRE(taxitask.get_time() == time);
    }

    SECTION("unassignment of an unassigned task")
    {
        task.unassign();
        REQUIRE(task.get_status() == TaskStatus::unassigned);
    }

    SECTION("get assignee without previous assignment")
    {
        REQUIRE_THROWS_AS(smalltask.get_assignee(), TaskStatusError);;
    }

    SECTION("assignment")
    {
        taxitask.assign(cook);
        REQUIRE(smalltask.get_assignee() == cook);
        REQUIRE(task.get_status() == TaskStatus::assigned);
    }

    SECTION("unassignment")
    {
        taxitask.assign(cook);
        task.unassign();
        REQUIRE(task.get_status() == TaskStatus::unassigned);
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
