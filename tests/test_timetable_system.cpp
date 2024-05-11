#include "catch_amalgamated.hpp"
#include "../src/systems/timetable_system.hpp"
#include "../src/types/datetime.h"


TEST_CASE("Test TimetableSystem")
{
    TimetableSystem tt_system{};
    WorkerSystem w_system{};
    tt_system.bind_worker_system(w_system);
    Pay pay{PaycheckMethod::Salary, Amount{0, 0}};
    Receptionist receptionist{"name", "id1", pay};
    jed_utils::datetime date1{ 2024, 4, 11 };
    const auto& entries = tt_system.get_entries();

    REQUIRE( &tt_system.get_worker_system() == &w_system );

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
        Receptionist waiter{"name", "id2", pay};
        jed_utils::datetime date1{ 2024, 4, 11 };
        jed_utils::datetime date2{ 2024, 4, 12 };
        TimetableEntry entry1{receptionist, date1, Shift::I};
        TimetableEntry entry2{waiter, date2, Shift::II};
        TimetableEntry entry3{receptionist, date2, Shift::III};
        tt_system.add_entry(entry1);
        tt_system.add_entry(entry2);
        tt_system.add_entry(entry3);
        auto receptionist_entries = tt_system.worker_entries(receptionist);
        REQUIRE( *receptionist_entries.at(0) == entry1 );
        REQUIRE( *receptionist_entries.at(1) == entry3 );
    }
}
