#include "catch_amalgamated.hpp"
#include "../src/workers/cook.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/types/pay.hpp"


TEST_CASE("Test Cook")
{
    auto w_system = WorkerSystem{};
    Amount salary_amount{3200, 0};
    Pay salary{PaycheckMethod::Salary, salary_amount};
    Amount wage_amount{25, 0};
    Pay wage{PaycheckMethod::Wage, wage_amount};

    SECTION("Regular interface")
    {
        Cook cook_obj{"1111", "name1", salary};
        w_system.add_worker(cook_obj);
        Cook* cook = &cook_obj;

        SECTION("init")
        {
            REQUIRE( cook -> get_type() == WorkerType::Cook );
        }
    }

    SECTION("Paycheck interface")
    {
        SECTION("regular")
        {
            Cook cook_obj{"1111", "name1", salary};
            w_system.add_worker(cook_obj);
            Cook* cook = &cook_obj;

            SECTION("init")
            {
                REQUIRE( cook -> get_dishes_prepared() == 0 );
            }

            SECTION("setters")
            {
                cook -> set_dishes_prepared(10);
                REQUIRE( cook -> get_dishes_prepared() == 10 );
            }
        }

        SECTION("bonus")
        {
            Cook cook_obj{"1111", "name1", salary};
            w_system.add_worker(cook_obj);
            Cook* cook = &cook_obj;

            cook -> set_dishes_prepared(10);
            REQUIRE( cook -> calculate_paycheck(0) ==
                cook -> calculate_base_paycheck(0) + Cook::get_bonus() * 10 );
        }

        SECTION("hours + bonus")
        {
            Cook cook_obj{"1111", "name1", wage};
            w_system.add_worker(cook_obj);
            Cook* cook = &cook_obj;

            cook -> set_dishes_prepared(10);
            REQUIRE( cook -> calculate_paycheck(15) == wage.get_wage() * 15 + Cook::get_bonus() * 10 );
        }
    }

    SECTION("TimeTable interface")
    {
        Cook cook_obj{"1111", "name1", salary};
        w_system.add_worker(cook_obj);
        Worker* cook = &cook_obj;

        REQUIRE( cook -> get_shifts() == 1 );
        REQUIRE( cook -> get_shift_start(Shift::I) == jed_utils::timespan{0, 8} );
        REQUIRE_THROWS( cook -> get_shift_start(Shift::II) );
        REQUIRE( cook -> get_shift_duration() == jed_utils::timespan{0, 12} );
    }
}
