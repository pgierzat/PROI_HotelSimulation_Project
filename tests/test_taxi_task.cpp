#include "catch_amalgamated.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/systems/task_system.hpp"
#include "../src/tasks/taxi_task.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test TaxiTask")
{
    WorkerSystem w_system{};
    RoomsList rooms_list{};
    GuestSystem g_system{};
    Guest guest1{"id1", "name1"};
    g_system.add_guest(guest1);
    TaskSystem t_system{w_system, rooms_list, g_system};
    
    jed_utils::datetime time{2024, 5, 18, 6, 45};
    TaxiTask taxitask{"1111", guest1, time};
    Task& task = taxitask;

    SECTION("init")
    {
        REQUIRE(task.get_description() == "Order a taxi for a guest.");
        REQUIRE(taxitask.get_guest() == guest1);
        REQUIRE(taxitask.get_time() == time);
    }
}
