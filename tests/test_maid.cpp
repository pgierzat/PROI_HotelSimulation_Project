#include "catch_amalgamated.hpp"
#include "../src/workers/maid.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/types/pay.hpp"


TEST_CASE("Test Maid")
{
    auto w_system = WorkerSystem{};
    Amount salary_amount{3200, 0};
    Pay salary{PaycheckMethod::Salary, salary_amount};
    Amount wage_amount{25, 0};
    Pay wage{PaycheckMethod::Wage, wage_amount};

    SECTION("Regular interface")
    {
        Maid maid_obj{"name1", "1111", salary};
        w_system.add_worker(maid_obj);
        Maid* maid = &maid_obj;

        SECTION("init")
        {
            REQUIRE( maid -> get_type() == WorkerType::Maid );
        }
    }

    SECTION("Paycheck interface")
    {
        SECTION("regular")
        {
            Maid maid_obj{"name1", "1111", salary};
            w_system.add_worker(maid_obj);
            Maid* maid = &maid_obj;

            SECTION("init")
            {
                REQUIRE( maid -> get_rooms_serviced() == 0 );
            }

            SECTION("setters")
            {
                maid -> set_rooms_serviced(10);
                REQUIRE( maid -> get_rooms_serviced() == 10 );
            }
        }

        SECTION("bonus")
        {
            Maid maid_obj{"name1", "1111", salary};
            w_system.add_worker(maid_obj);
            Maid* maid = &maid_obj;

            maid -> set_rooms_serviced(10);
            REQUIRE( maid -> calculate_paycheck(0) ==
                maid -> calculate_base_paycheck(0) + Maid::bonus * 10 );
        }

        SECTION("hours + bonus")
        {
            Maid maid_obj{"name1", "1111", wage};
            w_system.add_worker(maid_obj);
            Maid* maid = &maid_obj;

            maid -> set_rooms_serviced(10);
            REQUIRE( maid -> calculate_paycheck(15) == wage.get_wage() * 15 + Maid::bonus * 10 );
        }
    }

    SECTION("TimeTable interface")
    {
        Maid maid_obj{"name1", "1111", salary};
        w_system.add_worker(maid_obj);
        Worker* maid = &maid_obj;

        REQUIRE( maid -> get_shifts() == 2 );
        REQUIRE( maid -> get_shift_start(Shift::I) == jed_utils::timespan{0, 8} );
        REQUIRE( maid -> get_shift_start(Shift::II) == jed_utils::timespan{0, 14} );
        REQUIRE_THROWS( maid -> get_shift_start(Shift::III) );
        REQUIRE( maid -> get_shift_duration() == jed_utils::timespan{0, 6} );
    }
}
