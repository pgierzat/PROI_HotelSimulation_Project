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
}
