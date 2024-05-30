#include "catch_amalgamated.hpp"
#include "../src/types/paycheck.hpp"
#include "../src/workers/waiter.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/systems/timetable_system.hpp"
#include "../src/systems/paycheck_system.hpp"


TEST_CASE("Test Paycheck")
{
    Amount salary_amount{3200, 0};
    Pay salary{PaycheckMethod::Salary, salary_amount};
    auto w_system = WorkerSystem{};
    Waiter waiter{"id1", "name1", salary};
    w_system.add_worker(waiter);
    auto tt_system = TimetableSystem{w_system};
    auto pc_system = PaycheckSystem{w_system, tt_system};

    SECTION("init")
    {
        Amount amount{4000, 0};
        Paycheck paycheck{waiter, amount};
        REQUIRE( paycheck.get_worker() == waiter );
        REQUIRE( paycheck.get_amount() == amount );
    }
}