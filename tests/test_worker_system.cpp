#include "catch_amalgamated.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/workers/worker.hpp"
#include "../src/workers/maid.hpp"
#include "../src/workers/receptionist.hpp"
#include "../src/workers/waiter.hpp"
#include "../src/types/pay.hpp"
#include <memory>
#include <iostream>


TEST_CASE("Test WorkerSystem")
{
    WorkerSystem system{};
    Pay pay{PaycheckMethod::Salary, Amount{0, 0}};
    Cook cook{"name1", "1111", pay};
    Maid maid{"name2", "2222", pay};
    Receptionist receptionist{"name3", "3333", pay};
    Waiter waiter{"name4", "4444", pay};

    system.add_worker(cook);
    system.add_worker(maid);
    system.add_worker(receptionist);
    system.add_worker(waiter);
    auto workers = system.get_workers();

    SECTION("simple use")
    {
        REQUIRE( cook == *workers.at(0) );
        REQUIRE( maid == *workers.at(1) );
        REQUIRE( receptionist == *workers.at(2) );
        REQUIRE( waiter == *workers.at(3) );

    }

    SECTION("duplicate id")
    {
        Waiter waiter{"name3", "2222", pay};
        REQUIRE_THROWS( system.add_worker(waiter) );
    }

    SECTION("find by id hit")
    {
        const Worker& found_worker = *system.find_by_id("2222").value();
        REQUIRE( found_worker == maid );
    }

    SECTION("find by id miss")
    {
        REQUIRE( system.find_by_id("5555") == std::nullopt );
    }

    SECTION("set dishes prepared")
    {
        system.set_dishes_prepared(cook, 5);
        auto real_cook = dynamic_cast<const Cook*>( system.find_by_id(cook.get_id()).value() );
        REQUIRE( real_cook -> get_dishes_prepared() == 5 );
    }

    SECTION("set rooms serviced")
    {
        system.set_rooms_serviced(maid, 5);
        auto real_maid = dynamic_cast<const Maid*>( system.find_by_id(maid.get_id()).value() );
        REQUIRE( real_maid -> get_rooms_serviced() == 5 );
    }

    SECTION("set complaints")
    {
        system.set_complaints(receptionist, 5);
        auto real_receptionist = dynamic_cast<const Receptionist*>( system.find_by_id(receptionist.get_id()).value() );
        REQUIRE( real_receptionist -> get_complaints() == 5 );
    }

    SECTION("set orders taken")
    {
        system.set_orders_taken(waiter, 5);
        auto real_waiter = dynamic_cast<const Waiter*>( system.find_by_id(waiter.get_id()).value() );
        REQUIRE( real_waiter -> get_orders_taken() == 5 );
    }

    SECTION("reset stats")
    {
        system.set_dishes_prepared(cook, 5);
        system.set_rooms_serviced(maid, 5);
        system.set_complaints(receptionist, 5);
        system.set_orders_taken(waiter, 5);
        auto real_cook = dynamic_cast<const Cook*>( system.find_by_id(cook.get_id()).value() );
        auto real_maid = dynamic_cast<const Maid*>( system.find_by_id(maid.get_id()).value() );
        auto real_waiter = dynamic_cast<const Waiter*>( system.find_by_id(waiter.get_id()).value() );
        auto real_receptionist = dynamic_cast<const Receptionist*>( system.find_by_id(receptionist.get_id()).value() );
        system.reset_stats();
        REQUIRE( real_cook -> get_dishes_prepared() == 0 );
        REQUIRE( real_maid -> get_rooms_serviced() == 0 );
        REQUIRE( real_receptionist -> get_complaints() == 0 );
        REQUIRE( real_waiter -> get_orders_taken() == 0 );
    }
}
