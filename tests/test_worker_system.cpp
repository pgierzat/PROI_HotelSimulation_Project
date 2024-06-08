#include "catch_amalgamated.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/workers/worker.hpp"
#include "../src/workers/maid.hpp"
#include "../src/workers/receptionist.hpp"
#include "../src/workers/waiter.hpp"
#include <memory>
#include <iostream>


TEST_CASE("Test WorkerSystem")
{
    WorkerSystem w_system{};
    Pay pay{PaycheckMethod::Salary, Amount{0, 0}};
    Cook cook{"1111", "name1", pay};
    Maid maid{"2222", "name2", pay};
    Receptionist receptionist{"3333", "name3", pay};
    Waiter waiter{"4444", "name4", pay};

    w_system.add_worker(cook);
    w_system.add_worker(maid);
    w_system.add_worker(receptionist);
    w_system.add_worker(waiter);
    auto workers = w_system.get_workers();

    SECTION("simple use")
    {
        std::vector<const Worker*> exp{&cook, &maid, &receptionist, &waiter};
        REQUIRE( std::ranges::equal(workers, exp, [](auto p1, auto p2){ return *p1 == *p2; }) );
    }

    SECTION("duplicate id")
    {
        Waiter waiter2{"2222", "name5", pay};
        REQUIRE_THROWS_AS( w_system.add_worker(waiter2), DuplicateWorkerIDError );
    }

    SECTION("find by id hit")
    {
        const Worker& found_worker = *w_system.find_by_id("2222").value();
        REQUIRE( found_worker == maid );
    }

    SECTION("find by id miss")
    {
        REQUIRE( !w_system.find_by_id("5555") );
    }

    SECTION("set dishes prepared")
    {
        w_system.set_dishes_prepared(cook, 5);
        auto real_cook = dynamic_cast<const Cook*>( w_system.find_by_id(cook.get_id()).value() );
        REQUIRE( real_cook -> get_dishes_prepared() == 5 );
    }

    SECTION("set rooms serviced")
    {
        w_system.set_rooms_serviced(maid, 5);
        auto real_maid = dynamic_cast<const Maid*>( w_system.find_by_id(maid.get_id()).value() );
        REQUIRE( real_maid -> get_rooms_serviced() == 5 );
    }

    SECTION("set complaints")
    {
        w_system.set_complaints(receptionist, 5);
        auto real_receptionist = dynamic_cast<const Receptionist*>( w_system.find_by_id(receptionist.get_id()).value() );
        REQUIRE( real_receptionist -> get_complaints() == 5 );
    }

    SECTION("set orders taken")
    {
        w_system.set_orders_taken(waiter, 5);
        auto real_waiter = dynamic_cast<const Waiter*>( w_system.find_by_id(waiter.get_id()).value() );
        REQUIRE( real_waiter -> get_orders_taken() == 5 );
    }

    SECTION("reset stats")
    {
        w_system.set_dishes_prepared(cook, 5);
        w_system.set_rooms_serviced(maid, 5);
        w_system.set_complaints(receptionist, 5);
        w_system.set_orders_taken(waiter, 5);
        auto real_cook = dynamic_cast<const Cook*>( w_system.find_by_id(cook.get_id()).value() );
        auto real_maid = dynamic_cast<const Maid*>( w_system.find_by_id(maid.get_id()).value() );
        auto real_waiter = dynamic_cast<const Waiter*>( w_system.find_by_id(waiter.get_id()).value() );
        auto real_receptionist = dynamic_cast<const Receptionist*>( w_system.find_by_id(receptionist.get_id()).value() );
        w_system.reset_stats();
        REQUIRE( real_cook -> get_dishes_prepared() == 0 );
        REQUIRE( real_maid -> get_rooms_serviced() == 0 );
        REQUIRE( real_receptionist -> get_complaints() == 0 );
        REQUIRE( real_waiter -> get_orders_taken() == 0 );
    }

    SECTION("Test get_specific_workers")
    {
        Receptionist receptionist2{"5555", "name5", pay};
        w_system.add_worker(receptionist2);
        auto receptionists = w_system.get_specific_workers<Receptionist>();
        auto exp = std::vector<const Receptionist*>{&receptionist, &receptionist2};
        REQUIRE(std::ranges::equal(receptionists, exp, [](auto p1, auto p2){ return *p1 == *p2; }));
    }

    SECTION("Test get_specific_workers, maid")
    {
        auto maid2 = Maid{"5555", "name5", pay};
        w_system.add_worker(maid2);
        auto receptionists = w_system.get_specific_workers<Maid>();
        auto exp = std::vector<const Maid*>{&maid, &maid2};
        REQUIRE(std::ranges::equal(receptionists, exp, [](auto p1, auto p2){ return *p1 == *p2; }));
    }
}
