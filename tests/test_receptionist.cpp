#include "catch_amalgamated.hpp"
#include "../src/workers/receptionist.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/types/pay.hpp"


TEST_CASE("Test Receptionist")
{
    auto w_system = WorkerSystem{};
    Amount salary_amount{3200, 0};
    Pay salary{PaycheckMethod::Salary, salary_amount};
    Amount wage_amount{25, 0};
    Pay wage{PaycheckMethod::Wage, wage_amount};

    SECTION("Regular interface")
    {
        Receptionist receptionist_obj{"id1", "name1", salary};
        w_system.add_worker(receptionist_obj);
        Receptionist* receptionist = &receptionist_obj;

        SECTION("init")
        {
            REQUIRE( receptionist -> get_type() == WorkerType::Receptionist );
        }
    }

    SECTION("Paycheck interface")
    {
        SECTION("regular")
        {
            Receptionist receptionist_obj{"id1", "name1", salary};
            w_system.add_worker(receptionist_obj);
            Receptionist* receptionist = &receptionist_obj;

            SECTION("init")
            {
                REQUIRE( receptionist -> get_complaints() == 0 );
            }

            SECTION("setters")
            {
                receptionist -> set_complaints(10);
                REQUIRE( receptionist -> get_complaints() == 10 );
            }
        }

        SECTION("bonus")
        {
            Receptionist receptionist_obj{"id1", "name1", salary};
            w_system.add_worker(receptionist_obj);
            Receptionist* receptionist = &receptionist_obj;

            receptionist -> set_complaints(10);
            REQUIRE( receptionist -> calculate_paycheck(0) ==
                receptionist -> calculate_base_paycheck(0) - Receptionist::penalty * 10 );
        }

        SECTION("hours + bonus")
        {
            Receptionist receptionist_obj{"id1", "name1", wage};
            w_system.add_worker(receptionist_obj);
            Receptionist* receptionist = &receptionist_obj;

            receptionist -> set_complaints(10);
            REQUIRE( receptionist -> calculate_paycheck(15) ==
                wage.get_wage() * 15 - Receptionist::penalty * 10 );
        }
    }

    SECTION("TimeTable interface")
    {
        Receptionist receptionist_obj{"id1", "name1", salary};
        w_system.add_worker(receptionist_obj);
        Worker* receptionist = &receptionist_obj;

        REQUIRE( receptionist -> get_shifts() == 3 );
        REQUIRE( receptionist -> get_shift_start(Shift::I) == jed_utils::timespan{0, 6} );
        REQUIRE( receptionist -> get_shift_start(Shift::II) == jed_utils::timespan{0, 14} );
        REQUIRE( receptionist -> get_shift_start(Shift::III) == jed_utils::timespan{0, 22} );
        REQUIRE( receptionist -> get_shift_duration() == jed_utils::timespan{0, 8} );
    }
}
