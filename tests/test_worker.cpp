#include "catch_amalgamated.hpp"
#include "../src/workers/worker.hpp"
#include "../src/workers/cook.hpp"
#include "../src/types/pay.hpp"

TEST_CASE("Test Worker")
{
    Amount salary_amount{3200, 0};
    Pay salary{PaycheckMethod::Salary, salary_amount};
    Amount wage_amount{25, 0};
    Pay wage{PaycheckMethod::Wage, wage_amount};

    SECTION("Worker interface")
    {
        SECTION("Regular interface")
        {
            Cook cook_obj{"name1", "1111", salary};
            Worker* worker = &cook_obj;

            SECTION("init")
            {
                REQUIRE( worker -> get_name() == "name1" );
                REQUIRE( worker -> get_id() == "1111" );
            }

            SECTION("setters")
            {
                worker -> set_name("name2");
                worker -> set_id("2222");
                REQUIRE( worker -> get_name() == "name2" );
                REQUIRE( worker -> get_id() == "2222" );
            }
        }

        SECTION("Pay interface")
        {
            SECTION("Salary worker")
            {
                Cook cook_obj{"name1", "1111", salary};
                Worker* worker = &cook_obj;

                SECTION("init")
                {
                    REQUIRE( worker -> get_pay() == salary );
                    REQUIRE( worker -> get_hours_worked() == 0 );
                    REQUIRE( worker -> calculate_base_paycheck() == salary_amount);
                }

                SECTION("setters")
                {
                    Pay npay{PaycheckMethod::Salary, Amount{3400, 0}};
                    worker -> set_pay(npay);
                    worker -> set_hours_worked(10);
                    REQUIRE( worker -> get_pay() == npay );
                    REQUIRE( worker -> get_hours_worked() == 10 );
                }

                SECTION("hours worked, doesn't affect base paycheck")
                {
                    worker -> set_hours_worked(10);
                    REQUIRE( worker -> calculate_base_paycheck() == salary_amount);
                }
            }

            SECTION("Wage worker")
            {
                Cook cook_obj{"name1", "1111", wage};
                Worker* worker = &cook_obj;

                SECTION("init")
                {
                    REQUIRE( worker -> get_pay() == wage );
                    REQUIRE( worker -> get_hours_worked() == 0 );
                    REQUIRE( worker -> calculate_base_paycheck() == Amount{0, 0} );
                }

                SECTION("setters")
                {
                    Pay npay{PaycheckMethod::Wage, Amount{30, 0}};
                    worker -> set_pay(npay);
                    worker -> set_hours_worked(10);
                    REQUIRE( worker -> get_pay() == npay );
                    REQUIRE( worker -> get_hours_worked() == 10 );
                }

                SECTION("hours worked, affects base paycheck")
                {
                    worker -> set_hours_worked(10);
                    REQUIRE( worker -> calculate_base_paycheck() == wage_amount * 10 );
                }
            }
        }
    }
}
