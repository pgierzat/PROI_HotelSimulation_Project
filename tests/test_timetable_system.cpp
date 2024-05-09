#include "catch_amalgamated.hpp"
#include "../src/systems/timetable_system.hpp"
#include "../src/types/datetime.h"


TEST_CASE("Test TimetableSystem init")
{
    TimetableSystem tt_system{};
    WorkerSystem w_system{};
    tt_system.bind_worker_system(w_system);
    REQUIRE( &tt_system.get_worker_system() == &w_system );
}

TEST_CASE("Test TimetableSystem add_entry")
{
    TimetableSystem tt_system{};
    WorkerSystem w_system{};
    tt_system.bind_worker_system(w_system);

    Pay pay{PaycheckMethod::Salary};
    Receptionist receptionist{"name", "id1", pay};
    jed_utils::datetime date1{ 2024, 4, 11 };
    TimetableEntry entry1{receptionist, date1, Shift::I};
    const auto& entries = tt_system.get_entries();
    tt_system.add_entry(entry1);    
    REQUIRE( entries[0] == entry1 );
}

TEST_CASE("Test TimetableSystem remove_entry")
{
    TimetableSystem tt_system{};
    WorkerSystem w_system{};
    tt_system.bind_worker_system(w_system);

    Pay pay{PaycheckMethod::Salary};
    Receptionist receptionist{"name", "id1", pay};
    jed_utils::datetime date1{ 2024, 4, 11 };
    jed_utils::datetime date2{ 2024, 4, 12 };
    jed_utils::datetime date3{ 2024, 4, 13 };
    TimetableEntry entry1{receptionist, date1, Shift::I};
    TimetableEntry entry2{receptionist, date2, Shift::II};
    TimetableEntry entry3{receptionist, date3, Shift::III};
    const auto& entries = tt_system.get_entries();

    tt_system.add_entry(entry1);
    tt_system.add_entry(entry2);
    tt_system.add_entry(entry3);
    
    tt_system.remove_entry(entry2);
    REQUIRE( entries[0] == entry1 );
    REQUIRE( entries[1] == entry3 );
}

TEST_CASE("Test TimetableSystem add_entry less than 11-hour's break")
{
    TimetableSystem tt_system{};
    WorkerSystem w_system{};
    tt_system.bind_worker_system(w_system);
    Pay pay{PaycheckMethod::Salary};
    Receptionist receptionist{"name", "id", pay};
    jed_utils::datetime date1{ 2024, 4, 11 };
    jed_utils::datetime date2{ 2024, 4, 12 };
    TimetableEntry entry1{receptionist, date1, Shift::II};
    TimetableEntry entry2{receptionist, date2, Shift::I};
    tt_system.add_entry(entry1);
    REQUIRE_THROWS( tt_system.add_entry(entry2) );
}

TEST_CASE("Test TimetableSystem worker_entries")
{
    TimetableSystem tt_system{};
    WorkerSystem w_system{};
    tt_system.bind_worker_system(w_system);

    Pay pay{PaycheckMethod::Salary};
    Receptionist receptionist{"name", "id1", pay};
    Receptionist waiter{"name", "id2", pay};
    jed_utils::datetime date1{ 2024, 4, 11 };
    jed_utils::datetime date2{ 2024, 4, 12 };
    TimetableEntry entry1{receptionist, date1, Shift::I};
    TimetableEntry entry2{waiter, date2, Shift::II};
    TimetableEntry entry3{receptionist, date2, Shift::III};
    tt_system.add_entry(entry1);
    tt_system.add_entry(entry2);
    tt_system.add_entry(entry3);
    const auto& entries = tt_system.worker_entries(receptionist);

    REQUIRE( *entries[0] == entry1);
    REQUIRE( *entries[1] == entry3);
}
