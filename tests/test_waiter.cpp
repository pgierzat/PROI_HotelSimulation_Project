#include "catch_amalgamated.hpp"
#include "../src/workers/waiter.hpp"
#include "../src/types/pay.hpp"


TEST_CASE("Test Waiter")
{
    Amount salary_amount{3200, 0};
    Pay salary{PaycheckMethod::Salary, salary_amount};
    Amount wage_amount{25, 0};
    Pay wage{PaycheckMethod::Wage, wage_amount};

    SECTION("Regular interface")
    {
        Waiter waiter_obj{"name1", "1111", salary};
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
            Waiter waiter_obj{"name1", "1111", salary};
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
            Waiter waiter_obj{"name1", "1111", salary};
            Waiter* waiter = &waiter_obj;

            waiter -> set_orders_taken(10);
            REQUIRE( waiter -> calculate_paycheck() ==
                waiter -> calculate_base_paycheck() + Waiter::bonus * 10 );
        }

        SECTION("hours + bonus")
        {
            Waiter waiter_obj{"name1", "1111", wage};
            Waiter* waiter = &waiter_obj;

            waiter -> set_hours_worked(15);
            waiter -> set_orders_taken(10);
            REQUIRE( waiter -> calculate_paycheck() ==
                wage.get_wage() * 15 + Waiter::bonus * 10 );
        }
    }

    SECTION("TimeTable interface")
    {
        Waiter waiter_obj{"name1", "1111", salary};
        Worker* waiter = &waiter_obj;

        REQUIRE( waiter -> get_shifts() == 1 );
        REQUIRE( waiter -> get_shift_start(Shift::I) == jed_utils::timespan{0, 8} );
        REQUIRE_THROWS( waiter -> get_shift_start(Shift::II) );
        REQUIRE( waiter -> get_shift_duration() == jed_utils::timespan{0, 12} );
    }
}
