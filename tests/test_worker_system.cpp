#include "/opt/catch_amalgamated.hpp"
#include "../src/worker_system.hpp"
#include "../src/workers/worker.hpp"
#include "../src/workers/maid.hpp"
#include "../src/workers/receptionist.hpp"
#include "../src/workers/waiter.hpp"
#include "../src/pay.hpp"
#include <memory>
#include <iostream>


TEST_CASE("Test WorkerSystem add")
{
    WorkerSystem system{};
    Pay pay{};
    Maid maid{"name1", "1111", pay};
    Receptionist receptionist{"name2", "2222", pay};
    system.add_worker(maid);
    system.add_worker(receptionist);
    auto workers = system.get_workers();
    REQUIRE( maid == *workers[0] );
    REQUIRE( receptionist == *workers[1] );

    Waiter waiter{"name3", "2222", pay};
    REQUIRE_THROWS( system.add_worker(waiter) );
}

TEST_CASE("Test WorkerSystem find_worker_by_id")
{
    WorkerSystem system{};
    Pay pay{};
    Maid maid{"name1", "1111", pay};
    Receptionist receptionist{"name2", "2222", pay};
    system.add_worker(maid);
    system.add_worker(receptionist);
    const Worker& found_worker = *system.find_worker_by_id("2222").value();
    REQUIRE( found_worker == receptionist );
    REQUIRE( system.find_worker_by_id("3333") == std::nullopt );
}
