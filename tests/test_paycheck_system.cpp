#include "catch_amalgamated.hpp"
#include "../src/systems/clock.hpp"
#include "../src/systems/paycheck_system.hpp"
#include "../src/functions/equal_operators.hpp"

TEST_CASE("Test PaycheckSystem")
{
    using namespace std::chrono;

    jed_utils::datetime time0{2024y/May/11d};
    Clock ck{time0};
    WorkerSystem w_system{};
<<<<<<< HEAD
    TimetableSystem tt_system{ck, w_system};
    PaycheckSystem pc_system{ck, w_system, tt_system};
=======
    TimetableSystem tt_system{w_system};
    PaycheckSystem pc_system{ck, w_system, tt_system};
    const auto& paychecks = pc_system.get_paychecks();
>>>>>>> main

    Amount amount1{3200, 0};
    Amount amount2{20, 0};
    Pay salary1{PaycheckMethod::Salary, amount1};
    Pay wage1{PaycheckMethod::Wage, amount2};
    w_system.add_worker(Waiter{"id1", "name1", salary1});
    w_system.add_worker(Maid{"id2", "name2", wage1});
    auto& waiter = w_system.get_by_id("id1");
    auto& maid = w_system.get_by_id("id2");

    jed_utils::datetime date1{2024y/May/12d};
    jed_utils::datetime date2{2024y/May/14d};
    tt_system.add_entry(TimetableEntry{"id1", waiter, date1, Shift::I});
    tt_system.add_entry(TimetableEntry{"id2", maid, date2, Shift::II});

    SECTION("simple use")
    {
        REQUIRE( pc_system.get_paychecks().empty() );
        jed_utils::datetime time2{2024y/June/1d};
        ck.set_time(time2);
        Paycheck exp_waiter_pc{waiter, amount1};
        Paycheck exp_maid_pc{maid, amount2 * maid.get_shift_duration().get_hours()};
        std::vector expected_pcs1{exp_waiter_pc, exp_maid_pc};
        REQUIRE( pc_system.get_paychecks() == expected_pcs1 );
        jed_utils::datetime time3{2024y/June/2d};
        ck.set_time(time3);
        REQUIRE( pc_system.get_paychecks() == expected_pcs1 );
        jed_utils::datetime time4{2024y/July/2d};
        ck.set_time(time4);
        std::vector expected_pcs2{exp_waiter_pc};
        REQUIRE( pc_system.get_paychecks() == expected_pcs2 );
    }
}