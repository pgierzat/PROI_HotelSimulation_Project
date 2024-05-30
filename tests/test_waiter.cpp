#include "catch_amalgamated.hpp"
#include "../src/workers/waiter.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/types/pay.hpp"


TEST_CASE("Test Waiter")
{
    auto w_system = WorkerSystem{};
    Amount salary_amount{3200, 0};
    Pay salary{PaycheckMethod::Salary, salary_amount};
    Amount wage_amount{25, 0};
    Pay wage{PaycheckMethod::Wage, wage_amount};

    SECTION("Regular interface")
    {
        Waiter waiter_obj{"id1", "name1", salary};
        w_system.add_worker(waiter_obj);
        Waiter* waiter = &waiter_obj;

        SECTION("init")
        {
            REQUIRE( waiter -> get_type() == WorkerType::Waiter );
        }
    }

    SECTION("Paycheck interface")
    {
        SECTION("regular")
        {
            Waiter waiter_obj{"id1", "name1", salary};
            w_system.add_worker(waiter_obj);
            Waiter* waiter = &waiter_obj;

            SECTION("init")
            {
                REQUIRE( waiter -> get_orders_taken() == 0 );
            }

            SECTION("setters")
            {
                waiter -> set_orders_taken(10);
                REQUIRE( waiter -> get_orders_taken() == 10 );
            }
        }

        SECTION("bonus")
        {
            Waiter waiter_obj{"id1", "name1", salary};
            w_system.add_worker(waiter_obj);
            Waiter* waiter = &waiter_obj;

            waiter -> set_orders_taken(10);
            REQUIRE( waiter -> calculate_paycheck(0) ==
                waiter -> calculate_base_paycheck(0) + Waiter::bonus * 10 );
        }

        SECTION("hours + bonus")
        {
            Waiter waiter_obj{"id1", "name1", wage};
            w_system.add_worker(waiter_obj);
            Waiter* waiter = &waiter_obj;

            waiter -> set_orders_taken(10);
            REQUIRE( waiter -> calculate_paycheck(15) ==
                wage.get_wage() * 15 + Waiter::bonus * 10 );
        }
    }

    SECTION("TimeTable interface")
    {
        Waiter waiter_obj{"id1", "name1", salary};
        w_system.add_worker(waiter_obj);
        Worker* waiter = &waiter_obj;

        REQUIRE( waiter -> get_shifts() == 1 );
        REQUIRE( waiter -> get_shift_start(Shift::I) == jed_utils::timespan{0, 8} );
        REQUIRE_THROWS( waiter -> get_shift_start(Shift::II) );
        REQUIRE( waiter -> get_shift_duration() == jed_utils::timespan{0, 12} );
    }
}
