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


TEST_CASE("Test Maid, interface")
{
    Maid maid_obj{"maid", "123", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
    Worker* maid = &maid_obj;
    REQUIRE( maid -> get_shifts() == 2 );
    REQUIRE( maid -> get_shift_start(Shift::I) == jed_utils::timespan{0, 8} );
    REQUIRE( maid -> get_shift_start(Shift::II) == jed_utils::timespan{0, 14} );
    REQUIRE_THROWS( maid -> get_shift_start(Shift::III) );
    REQUIRE( maid -> get_shift_duration() == jed_utils::timespan{0, 6} );
}

TEST_CASE("Test Receptionist, interface")
{
    Receptionist receptionist_obj{"receptionist", "123", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
    Worker* receptionist = &receptionist_obj;
    REQUIRE( receptionist -> get_shifts() == 3 );
    REQUIRE( receptionist -> get_shift_start(Shift::I) == jed_utils::timespan{0, 6} );
    REQUIRE( receptionist -> get_shift_start(Shift::II) == jed_utils::timespan{0, 14} );
    REQUIRE( receptionist -> get_shift_start(Shift::III) == jed_utils::timespan{0, 22} );
    REQUIRE( receptionist -> get_shift_duration() == jed_utils::timespan{0, 8} );
}

TEST_CASE("Test Waiter, interface")
{
    Waiter waiter_obj{"waiter", "123", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
    Worker* waiter = &waiter_obj;
    REQUIRE( waiter -> get_shifts() == 1 );
    REQUIRE( waiter -> get_shift_start(Shift::I) == jed_utils::timespan{0, 8} );
    REQUIRE_THROWS( waiter -> get_shift_start(Shift::II) );
    REQUIRE( waiter -> get_shift_duration() == jed_utils::timespan{0, 12} );
}