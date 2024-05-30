#include "catch_amalgamated.hpp"
#include "../src/systems/paycheck_system.hpp"

TEST_CASE("Test PaycheckSystem")
{
    using namespace std::chrono;

    WorkerSystem w_system{};
    TimetableSystem tt_system{w_system};
    PaycheckSystem pc_system{w_system, tt_system};
    const auto& paychecks = pc_system.get_paychecks();

    Amount amount1{3200, 0};
    Pay salary1{PaycheckMethod::Salary, amount1};
    Waiter waiter{"id1", "name1", salary1};
    w_system.add_worker(waiter);
    Amount amount2{20, 0};
    Pay wage1{PaycheckMethod::Wage, amount2};
    Maid maid{"id2", "name2", wage1};
    w_system.add_worker(maid);

    jed_utils::datetime date1{2024y/May/12d};
    TimetableEntry entry1{waiter, date1, Shift::I};
    tt_system.add_entry(entry1);
    jed_utils::datetime date2{2024y/May/14d};
    TimetableEntry entry2{maid, date2, Shift::II};
    tt_system.add_entry(entry2);

    SECTION("simple use")
    {
        REQUIRE( paychecks.empty() );
        jed_utils::datetime time1{2024y/May/11d};
        pc_system.set_time(time1);
        Paycheck exp_waiter_pc{waiter, amount1};
        std::vector expected_pcs1{exp_waiter_pc};
        REQUIRE( paychecks == expected_pcs1 );
        jed_utils::datetime time2{2024y/June/1d};
        pc_system.set_time(time2);
        Paycheck exp_maid_pc{maid, amount2 * maid.get_shift_duration().get_hours()};
        std::vector expected_pcs2{exp_waiter_pc, exp_maid_pc};
        REQUIRE( paychecks == expected_pcs2 );
        jed_utils::datetime time3{2024y/June/2d};
        pc_system.set_time(time3);
        REQUIRE( paychecks == expected_pcs2 );
        jed_utils::datetime time4{2024y/July/2d};
        pc_system.set_time(time4);
        REQUIRE( paychecks == expected_pcs1 );
    }

    SECTION("turn back time")
    {
        jed_utils::datetime time1{2024y/May/11d};
        pc_system.set_time(time1);
        jed_utils::datetime time2{2024y/May/10d};
        REQUIRE_THROWS_AS( pc_system.set_time(time2), TurnBackTimeError );
    }
}