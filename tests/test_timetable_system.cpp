#include "catch_amalgamated.hpp"
#include "../src/systems/timetable_system.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/systems/clock.hpp"
#include "../src/types/datetime.h"
#include "../src/functions/tt_system_aux.hpp"
#include "../src/functions/vec_to_pvec.hpp"
#include <ranges>


TEST_CASE("Test TimetableSystem")
{
    using namespace std::chrono;

    WorkerSystem w_system{};
    Pay pay{PaycheckMethod::Salary, Amount{0, 0}};
    w_system.add_worker(Receptionist{"id1", "name1", pay});
    w_system.add_worker(Waiter{"id2", "name2", pay});
    auto& waiter = w_system.get_by_id("id1"); 
    auto& receptionist = w_system.get_by_id("id2"); 
    TimetableSystem tt_system{w_system};
    jed_utils::datetime date0{ 2024, 4, 10 };
    Clock ck{date0};
    ck.subscribe(tt_system);
    const auto& entries = tt_system.get_entries();

    SECTION("init") { REQUIRE(entries.empty()); }
    
    jed_utils::datetime date1{ 2024, 4, 11 };
    jed_utils::datetime date2{ 2024, 4, 12 };
    jed_utils::datetime date3{2024, 5, 3};
    tt_system.add_entry(TimetableEntry{"id1", receptionist, date1, Shift::II});
    tt_system.add_entry(TimetableEntry{"id2", waiter, date2, Shift::I});
    tt_system.add_entry(TimetableEntry{"id3", waiter, date3, Shift::I});
    auto& entry1 = tt_system.get_by_id("id1");
    auto& entry2 = tt_system.get_by_id("id2");
    auto& entry3 = tt_system.get_by_id("id3");

    SECTION("simple use")
    {
        std::vector expected1{entry1, entry2, entry3};
        REQUIRE( entries == expected1 );
        tt_system.remove_entry(entry1);
        std::vector expected2{entry2, entry3};
        REQUIRE( entries == expected2 );
    }

    SECTION("add entry of an unknown worker")
    {
        Cook cook{"id3", "name3", pay};
        TimetableEntry entry4{"id4", cook, date1, Shift::I};
        REQUIRE_THROWS_AS(tt_system.add_entry(entry4), WorkerNotInSystemError);
    }

    SECTION("add_entry, less than 11-hour's break")
    {
        jed_utils::datetime date4{2024, 4, 10};
        TimetableEntry entry4{"id4", receptionist, date4, Shift::III};
        REQUIRE_THROWS( tt_system.add_entry(entry4) );
    }

    SECTION("entry status")
    {
        jed_utils::datetime date4{2024, 4, 15};
        TimetableEntry entry4{"id4", waiter, date4, Shift::I};
        jed_utils::datetime before{2024, 4, 15, 7};
        jed_utils::datetime during{2024, 4, 15, 12};
        jed_utils::datetime after{2024, 4, 15, 20, 40};
        ck.set_time(before);
        REQUIRE( tt_system.get_entry_status(entry4) == EntryStatus::scheduled );
        ck.set_time(during);
        REQUIRE( tt_system.get_entry_status(entry4) == EntryStatus::in_progress );
        ck.set_time(after);
        REQUIRE( tt_system.get_entry_status(entry4) == EntryStatus::finished );
    }

    SECTION("interval entries")
    {
        auto int_entries = interval_entries(vec_to_pvec(entries), TimeInterval{date2, date3});
        std::vector exp{entry2, entry3};
        REQUIRE( std::ranges::equal(int_entries, exp, [](const auto e1, const auto& e2) { return *e1 == e2;}) );
    }

    SECTION("month entries")
    {
        auto int_entries = month_entries(vec_to_pvec(entries), 2024y / April);
        std::vector<TimetableEntry> exp{entry1, entry2};
        REQUIRE( std::ranges::equal(int_entries, exp, [](const auto e1, const auto& e2) { return *e1 == e2;}) );
    }

    SECTION("worker entries")
    {
        auto int_entries = worker_entries(vec_to_pvec(entries), waiter);
        std::vector<TimetableEntry> exp{entry2, entry3};
        REQUIRE( std::ranges::equal(int_entries, exp, [](const auto e1, const auto& e2) { return *e1 == e2;}) );
    }

    SECTION("worker available")
    {
        jed_utils::datetime during{ 2024, 4, 11, 16 };
        ck.set_time(during);
        auto w_available = tt_system.workers_available();
        std::vector<const Worker*> exp{&receptionist};
        REQUIRE( std::ranges::equal(w_available, exp, [](const auto e1, const auto e2) { return *e1 == *e2;}) );
    }
}
