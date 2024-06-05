#include "catch_amalgamated.hpp"
#include "../src/systems/task_system.hpp"

#include "../src/tasks/prepare_dish_task.hpp"
#include "../src/tasks/room_cleaning_task.hpp"
#include "../src/tasks/taxi_task.hpp"
#include "../src/tasks/bring_dish_task.hpp"
#include "../src/rooms/hpp/two_appartment.hpp"


TEST_CASE("Test TaskSystem")
{
    WorkerSystem w_system{};
    Pay pay{PaycheckMethod::Wage, Amount{22, 50}};
    Cook cook{"name1", "1111", pay};
    Maid maid1{"name2", "2222", pay};
    Maid maid2{"name3", "3333", pay};
    Receptionist receptionist{"name4", "4444", pay};
    Waiter waiter{"name5", "5555", pay};
    w_system.add_worker(cook);
    w_system.add_worker(maid1);
    w_system.add_worker(maid2);
    w_system.add_worker(receptionist);
    w_system.add_worker(waiter);
    RoomsList rooms_list{};
    GuestSystem g_system{};
    TaskSystem t_system{w_system, rooms_list, g_system};

    SECTION("init") { REQUIRE(t_system.get_tasks().empty()); }

    t_system.add_task(PrepareDishTask{"1", Dish::FrenchToasts});
    t_system.add_task(RoomCleaningTask{"2", TwoAppartment{"237"}});
    t_system.add_task(TaxiTask{"3", Guest{"id", "name"}, jed_utils::datetime{2024, 5, 19}});
    t_system.add_task(BringDishTask{"5", Dish::FrenchToasts, Table{"10"}});
    const auto& preptask = *t_system.find_by_id("1").value();
    const auto& roomtask = *t_system.find_by_id("2").value();
    const auto& taxitask = *t_system.find_by_id("3").value();
    const auto& bringtask = *t_system.find_by_id("5").value();

    SECTION("add task")
    {
        std::vector<const Task*> exp{&preptask, &roomtask, &taxitask, &bringtask};
        REQUIRE( std::ranges::equal(t_system.get_tasks(), exp, [](auto p1, auto p2){ return *p1 == *p2; }) );
    }

    SECTION("add_task_id, rvalue")
    {
        t_system.add_task_id(PrepareDishTask{"foo", Dish::FrenchToasts});
        REQUIRE(t_system.get_by_id("4") == PrepareDishTask{"4", Dish::FrenchToasts});
    }

    SECTION("add_task_id, lvalue")
    {
        auto task = PrepareDishTask{"foo", Dish::FrenchToasts};
        t_system.add_task_id(task);
        REQUIRE(t_system.get_by_id("4") == PrepareDishTask{"4", Dish::FrenchToasts});
    }

    SECTION("remove task")
    {
        t_system.remove_task(taxitask);
        std::vector<const Task*> exp{&preptask, &roomtask, &bringtask};
        REQUIRE( std::ranges::equal(t_system.get_tasks(), exp, [](auto p1, auto p2){ return *p1 == *p2; }) );
    }

    SECTION("find task by id")
    {
        auto opt = t_system.find_by_id(taxitask.get_id());
        REQUIRE( *opt.value() == taxitask );
    }
    
    SECTION("assign small task")
    {
        t_system.assign_task(taxitask, receptionist);
        auto task = t_system.find_by_id(taxitask.get_id()).value();
        REQUIRE( task -> get_status() == TaskStatus::assigned );
    }

    SECTION("assign big task")
    {
        t_system.assign_task(roomtask, maid1);
        t_system.assign_task(roomtask, maid2);
        auto task = t_system.find_by_id(roomtask.get_id()).value();
        REQUIRE( task -> get_status() == TaskStatus::assigned );
    }

    SECTION("invalid assignment, incorrect worker type")
    {
        REQUIRE_THROWS_AS( t_system.assign_task(taxitask, waiter), TaskAssignmentError );
    }

    SECTION("invalid assignment, unknown worker")
    {
        Receptionist receptionist2{"name6", "6666", pay};
        REQUIRE_THROWS_AS( t_system.assign_task(taxitask, receptionist2), WorkerNotInSystemError);
    }

    SECTION("complete task")
    {
        auto task = t_system.find_by_id(taxitask.get_id()).value();
        t_system.assign_task(taxitask, receptionist);
        t_system.complete_task(*task);
        REQUIRE( task -> get_status() == TaskStatus::completed );
    }

    SECTION("unassign")
    {
        auto task = t_system.find_by_id(taxitask.get_id()).value();
        t_system.assign_task(taxitask, receptionist);
        t_system.unassign_task(*task);
        REQUIRE( task -> get_status() == TaskStatus::unassigned );
    }
}
