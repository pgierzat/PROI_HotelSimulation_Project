#include "catch_amalgamated.hpp"
#include "../src/systems/timetable_system.hpp"
#include "../src/types/datetime.h"


TEST_CASE("Test TimetableSystem")
{
    TimetableSystem tt_system{};
    const auto& entries = tt_system.get_entries();

    SECTION("init") { REQUIRE(entries.empty()); }

    WorkerSystem w_system{};
    tt_system.bind_worker_system(w_system);
    Pay pay{PaycheckMethod::Salary, Amount{0, 0}};
    Receptionist receptionist{"name1", "id1", pay};
    Receptionist waiter{"name2", "id2", pay};
    w_system.add_worker(receptionist);
    w_system.add_worker(waiter);
    jed_utils::datetime date1{ 2024, 4, 11 };

    SECTION("simple use")
    {
        TimetableEntry entry1{receptionist, date1, Shift::I};
        jed_utils::datetime date2{ 2024, 4, 12 };
        TimetableEntry entry2{receptionist, date2, Shift::II};
        tt_system.add_entry(entry1);
        tt_system.add_entry(entry2);
        std::vector expected1{entry1, entry2};
        REQUIRE( entries == expected1 );
        tt_system.remove_entry(entry1);
        std::vector expected2{entry2};
        REQUIRE( entries == expected2 );
    }

    SECTION("add entry of an unknown worker")
    {
        Cook cook{"name3", "id3", pay};
        TimetableEntry entry1{cook, date1, Shift::I};
        REQUIRE_THROWS_AS(tt_system.add_entry(entry1), WorkerNotInSystemError);
    }

    SECTION("add_entry less than 11-hour's break")
    {
        jed_utils::datetime date1{ 2024, 4, 11 };
        jed_utils::datetime date2{ 2024, 4, 12 };
        TimetableEntry entry1{receptionist, date1, Shift::II};
        TimetableEntry entry2{receptionist, date2, Shift::I};
        tt_system.add_entry(entry1);
        REQUIRE_THROWS( tt_system.add_entry(entry2) );
    }

    SECTION("worker entries")
    {
        jed_utils::datetime date1{ 2024, 4, 11 };
        jed_utils::datetime date2{ 2024, 4, 12 };
        TimetableEntry entry1{receptionist, date1, Shift::I};
        TimetableEntry entry2{waiter, date2, Shift::II};
        TimetableEntry entry3{receptionist, date2, Shift::III};
        tt_system.add_entry(entry1);
        tt_system.add_entry(entry2);
        tt_system.add_entry(entry3);
        auto receptionist_entries = tt_system.worker_entries(receptionist);
        std::vector exp{entry1, entry3};
        REQUIRE( std::ranges::equal(receptionist_entries, exp,
            [](auto p, const auto& entry){ return *p == entry; }) );
    }

    SECTION("time test")
    {
        TimetableEntry entry1{receptionist, date1, Shift::I};
        std::vector exp{entry1};
        auto lambda = [](auto p, const auto& entry){ return *p == entry; };
        tt_system.add_entry(entry1);
        // uninitiated state
        REQUIRE( tt_system.get_active_entries().empty() );
        REQUIRE( tt_system.get_ending_entries().empty() );
        // before entry starts
        jed_utils::datetime start1{entry1.get_start()};
        jed_utils::datetime end1{entry1.get_end()};
        tt_system.set_time(start1 - jed_utils::timespan{1});
        REQUIRE( tt_system.get_active_entries().empty() );
        REQUIRE( tt_system.get_ending_entries().empty() );
        // entry starts
        tt_system.set_time(start1);
        std::ranges::equal(tt_system.get_active_entries(), exp, lambda);
        REQUIRE( tt_system.get_ending_entries().empty() );
        // entry hasn't yet end
        tt_system.set_time(end1 - jed_utils::timespan{0, 1});
        std::ranges::equal(tt_system.get_active_entries(), exp, lambda);
        REQUIRE( tt_system.get_ending_entries().empty() );
        //  entry ends
        tt_system.set_time(end1 + jed_utils::timespan{1});
        REQUIRE( tt_system.get_active_entries().empty() ); 
        std::ranges::equal(tt_system.get_ending_entries(), exp, lambda);
        // entry has ended before
        tt_system.set_time(end1 + jed_utils::timespan{2});
        REQUIRE( tt_system.get_active_entries().empty() ); 
        REQUIRE( tt_system.get_ending_entries().empty() );
    }
}
