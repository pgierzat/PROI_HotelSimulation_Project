#include "catch_amalgamated.hpp"
#include "../src/services/stay_service.hpp"
#include "../src/services/taxi_service.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/systems/stay_system.hpp"
#include "../src/systems/task_system.hpp"
#include "../src/systems/service_system.hpp"

TEST_CASE("Test ServiceSystem")
{
    RoomsList rooms_list{};
    rooms_list.add_two_room(237);
    const auto& room1 = *rooms_list.find_by_number(237).value();
    GuestSystem g_system{};
    Guest guest1{"id1", "name1"};
    Guest guest2{"id2", "name2"};
    g_system.add_guest(guest1);
    g_system.add_guest(guest2);
    WorkerSystem w_system{};
    auto pay = Pay{PaycheckMethod::Salary, Amount{3200, 0}};
    auto worker1 = Receptionist{"id1", "name1", pay};
    w_system.add_worker(worker1);
    StaySystem s_system{g_system, rooms_list};
    jed_utils::datetime start1{2024, 5, 21};
    jed_utils::datetime end1{2024, 5, 24};
    Stay stay1{"id1", room1, guest1, start1, end1};
    stay1.add_guest(guest2);
    s_system.add_stay(stay1);
    TaskSystem t_system{w_system, rooms_list, g_system};
    ServiceSystem sc_system{g_system, w_system, rooms_list, s_system, t_system};
    StayService stayservice{"1111", stay1};
    Service& service1 = stayservice;
    jed_utils::datetime time1{2024, 5, 23, 12, 15};
    TaxiService taxiservice{"2222", guest2, time1};
    Service& service2 = taxiservice;
    sc_system.add_service(stayservice);
    sc_system.add_service(taxiservice);

    SECTION("test get_default_price")
    {
        REQUIRE( service1.get_default_price() == room1.calculatePrice() * stay1.get_duration() );
    }

    SECTION("add")
    {
        REQUIRE( sc_system.get_by_id("1111") == service1 );
        REQUIRE( sc_system.get_by_id("2222") == service2 );
        REQUIRE_THROWS_AS( sc_system.get_by_id("3333"), ServiceNotInSystemError );
    }

    SECTION("refresh status")

    SECTION("mark as paid for")
    {
        REQUIRE_THROWS_AS( service1.mark_paid_for(), ServiceStatusError);
    }
}
