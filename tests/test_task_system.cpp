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
    w_system.add_worker(Cook{"1111", "id1", pay});
    w_system.add_worker(Maid{"2222", "id2", pay});
    w_system.add_worker(Maid{"3333", "id3", pay});
    w_system.add_worker(Receptionist{"4444", "id4", pay});
    w_system.add_worker(Waiter{"5555", "id5", pay});
    //auto& cook = w_system.get_by_id("1111");
    auto& maid1 = w_system.get_by_id("2222");
    auto& maid2 = w_system.get_by_id("3333");
    auto& receptionist = w_system.get_by_id("4444");
    auto& waiter = w_system.get_by_id("5555");
    RoomsList rooms_list{};
    rooms_list.add_room(TwoAppartment{"237"});
    auto& room1 = rooms_list.get_by_id("237");
    GuestSystem g_system{};
    g_system.add_guest(Guest{"id", "name"});
    auto& guest1 = g_system.get_by_id("id");
    TaskSystem t_system{w_system, rooms_list, g_system};

    SECTION("init") { REQUIRE(t_system.get_tasks().empty()); }

    t_system.add_task(PrepareDishTask{"1", Dish::FrenchToasts});
    t_system.add_task(RoomCleaningTask{"2", room1});
    t_system.add_task(TaxiTask{"3", guest1, jed_utils::datetime{2024, 5, 19}});
    t_system.add_task(BringDishTask{"5", Dish::FrenchToasts, "10"});
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
