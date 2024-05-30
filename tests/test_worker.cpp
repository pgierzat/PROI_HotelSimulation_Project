#include "catch_amalgamated.hpp"
#include "../src/workers/worker.hpp"
#include "../src/workers/cook.hpp"
#include "../src/types/pay.hpp"
#include "../src/systems/worker_system.hpp"

TEST_CASE("Test Worker")
{
    auto w_system = WorkerSystem{};
    Amount salary_amount{3200, 0};
    Pay salary{PaycheckMethod::Salary, salary_amount};
    Amount wage_amount{25, 0};
    Pay wage{PaycheckMethod::Wage, wage_amount};

    SECTION("Worker interface")
    {
        SECTION("Regular interface")
        {
            Cook cook_obj{"1111", "name1", salary};
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
                Cook cook_obj{"1111", "name1", salary};
                Worker* worker = &cook_obj;

                SECTION("init")
                {
                    REQUIRE( worker -> get_pay() == salary );
                    REQUIRE( worker -> calculate_base_paycheck(0) == salary_amount);
                }

                SECTION("setters")
                {
                    Pay npay{PaycheckMethod::Salary, Amount{3400, 0}};
                    worker -> set_pay(npay);
                    REQUIRE( worker -> get_pay() == npay );
                }

                SECTION("hours worked, doesn't affect base paycheck")
                {
                    REQUIRE( worker -> calculate_base_paycheck(10) == salary_amount);
                }
            }

            SECTION("Wage worker")
            {
                Cook cook_obj{"1111", "name1", wage};
                Worker* worker = &cook_obj;

                SECTION("init")
                {
                    REQUIRE( worker -> get_pay() == wage );
                    REQUIRE( worker -> calculate_base_paycheck(0) == Amount{0, 0} );
                }

                SECTION("setters")
                {
                    Pay npay{PaycheckMethod::Wage, Amount{30, 0}};
                    worker -> set_pay(npay);
                    REQUIRE( worker -> get_pay() == npay );
                }

                SECTION("hours worked, affects base paycheck")
                {
                    REQUIRE( worker -> calculate_base_paycheck(10) == wage_amount * 10 );
                }
            }
        }
    }
}
