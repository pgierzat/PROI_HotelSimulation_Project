#include "catch_amalgamated.hpp"
#include "../src/workers/cook.hpp"
#include "../src/types/pay.hpp"


TEST_CASE("Test Cook")
{
    Amount salary_amount{3200, 0};
    Pay salary{PaycheckMethod::Salary, salary_amount};
    Amount wage_amount{25, 0};
    Pay wage{PaycheckMethod::Wage, wage_amount};

    SECTION("Regular interface")
    {
        Cook cook_obj{"name1", "1111", salary};
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
            Cook cook_obj{"name1", "1111", salary};
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
            Cook cook_obj{"name1", "1111", salary};
            Cook* cook = &cook_obj;

            cook -> set_dishes_prepared(10);
            REQUIRE( cook -> calculate_paycheck() == cook -> calculate_base_paycheck() + Cook::bonus * 10 );
        }

        SECTION("hours + bonus")
        {
            Cook cook_obj{"name1", "1111", wage};
            Cook* cook = &cook_obj;

            cook -> set_hours_worked(15);
            cook -> set_dishes_prepared(10);
            REQUIRE( cook -> calculate_paycheck() == wage.get_wage() * 15 + Cook::bonus * 10 );
        }
    }

    SECTION("TimeTable interface")
    {
        Cook cook_obj{"name1", "1111", salary};
        Worker* cook = &cook_obj;

        REQUIRE( cook -> get_shifts() == 1 );
        REQUIRE( cook -> get_shift_start(Shift::I) == jed_utils::timespan{0, 8} );
        REQUIRE_THROWS( cook -> get_shift_start(Shift::II) );
        REQUIRE( cook -> get_shift_duration() == jed_utils::timespan{0, 12} );
    }
}
