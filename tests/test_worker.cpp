#include "catch_amalgamated.hpp"
#include "../src/workers/worker.hpp"
#include "../src/workers/cook.hpp"
#include "../src/workers/maid.hpp"
#include "../src/workers/receptionist.hpp"
#include "../src/workers/waiter.hpp"
#include "../src/types/pay.hpp"

TEST_CASE("Test salary Worker init")
{
    Cook cook_obj{"cook", "123", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
    Worker* cook = &cook_obj;
    REQUIRE( cook -> get_name() == "cook" );
    REQUIRE( cook -> get_id() == "123" );
    REQUIRE( cook -> get_paycheck_method() == PaycheckMethod::Salary );
    REQUIRE( cook -> get_salary() == Amount{3200, 0} );
    REQUIRE_THROWS( cook -> get_wage() );
    REQUIRE( cook -> get_hours_worked() == 0 );
}

TEST_CASE("Test wage Worker init")
{
    Cook cook_obj{"cook", "123", Pay{PaycheckMethod::Wage, Amount{20, 0}}};
    Worker* cook = &cook_obj;
    REQUIRE( cook -> get_paycheck_method() == PaycheckMethod::Wage );
    REQUIRE( cook -> get_wage() == Amount{20, 0} );
    REQUIRE_THROWS( cook -> get_salary() );
}

TEST_CASE("Test salary Worker setters")
{
    Cook cook_obj{"cook", "123", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
    Worker* cook = &cook_obj;
    cook -> set_hours_worked(1);
    REQUIRE( cook -> get_hours_worked() == 1 );
    cook -> set_salary(Amount{3300, 0});
    REQUIRE( cook -> get_salary() == Amount{3300, 0} );
    REQUIRE_THROWS(cook -> set_wage(Amount{20, 0}));
}

TEST_CASE("Test wage Worker setters")
{
    Cook cook_obj{"cook", "123", Pay{PaycheckMethod::Wage, Amount{20, 0}}};
    Worker* cook = &cook_obj;
    cook -> set_wage(Amount{22, 0});
    REQUIRE( cook -> get_wage() == Amount{22, 0} );
    REQUIRE_THROWS(cook -> set_salary(Amount{3200, 0}));
}

TEST_CASE("Test Cook, interface")
{
    Cook cook_obj{"cook", "123", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
    Worker* cook = &cook_obj;
    REQUIRE( cook -> get_shifts() == 1 );
    REQUIRE( cook -> get_shift_start(Shift::I) == jed_utils::timespan{0, 8} );
    REQUIRE_THROWS( cook -> get_shift_start(Shift::II) );
    REQUIRE( cook -> get_shift_duration() == jed_utils::timespan{0, 12} );
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