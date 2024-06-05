#include "catch_amalgamated.hpp"
#include "../src/services/stay_service.hpp"
#include "../src/workers/cook.hpp"
#include "../src/workers/receptionist.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/rooms/hpp/two_room.hpp"
#include "../src/systems/service_system.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/systems/task_system.hpp"
#include "../src/systems/stay_system.hpp"
#include "../src/utilities/errors.hpp"

TEST_CASE("Test Service")
{
    RoomsList rooms_list{};
    rooms_list.add_room(TwoRoom{"237"});
    const auto& room1 = rooms_list.get_by_id("237");
    GuestSystem g_system{};
    g_system.add_guest(Guest{"id1", "name1"});
    g_system.add_guest(Guest{"id2", "name2"});
    const auto& guest1 = *g_system.find_by_id("id1").value();
    const auto& guest2 = *g_system.find_by_id("id2").value();
    WorkerSystem w_system{};
    auto pay = Pay{PaycheckMethod::Wage, Amount{25, 0}};
    w_system.add_worker(Cook{"id1", "name1", pay});
    w_system.add_worker(Maid{"id2", "name2", pay});
    w_system.add_worker(Maid{"id3", "name3", pay});
    StaySystem s_system{g_system, rooms_list};
    jed_utils::datetime start1{2024, 5, 21};
    jed_utils::datetime end1{2024, 5, 24};
    s_system.add_stay(Stay{"id1", room1, guest1, start1, end1});
    auto& stay1 = s_system.get_by_id("id1");
    s_system.add_guest_to_stay(stay1, guest2);
    TaskSystem t_system{w_system, rooms_list, g_system};
    ServiceSystem sc_system{g_system, w_system, rooms_list, s_system, t_system};

    StayService stayservice{"1111", stay1};
    Service& service = stayservice;

    SECTION("init")
    {
        REQUIRE(service.get_description() == "Stay Service.");
        REQUIRE(service.get_id() == "1111");
        REQUIRE(service.get_price() == Amount{0, 0});
        REQUIRE(service.get_requestee() == guest1);
        REQUIRE(service.get_status() == ServiceStatus::ordered);
    }

    SECTION("set_price")
    {
        Amount price{15, 0};
        service.set_price(price);
        REQUIRE(service.get_price() == price);
    }

    SECTION("mark as paid for")
    {
        REQUIRE_THROWS_AS( service.mark_paid_for(), ServiceStatusError);
    }
}
