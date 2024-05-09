#include "/opt/catch_amalgamated.hpp"
#include "/opt/datetime.h"
#include "../src/timetable_entry.hpp"
#include "../src/workers/receptionist.hpp"
#include "../src/workers/maid.hpp"


TEST_CASE("Test TimetableEntry init")
{
    using namespace std::chrono;

    jed_utils::datetime date{ 2024, 4, 11, 2, 32, 55};
    jed_utils::datetime expected_date{ 2024, 4, 11 };
    jed_utils::datetime expected_start{ 2024, 4, 11, 22};
    jed_utils::datetime expected_end{ 2024, 4, 12, 6};
    TimeInterval expected_interval{expected_start, expected_end};
    Pay pay{};
    Receptionist receptionist{"name", "id", pay};
    TimetableEntry entry{receptionist, date, Shift::III};
    REQUIRE( entry.get_date() == expected_date );
    REQUIRE( entry.get_worker() == receptionist );
    REQUIRE( entry.get_shift() == Shift::III );
    REQUIRE( entry.get_interval() == expected_interval );
}


TEST_CASE("Test TimetableEntry init invalid")
{
    using namespace std::chrono;

    jed_utils::datetime date{ 2024, 4, 11 };
    Pay pay{};
    Maid maid{"name", "id", pay};
    // maids work 2 shifts
    REQUIRE_THROWS( TimetableEntry{maid, date, Shift::III} );
}


TEST_CASE("Test TimetableEntry operator==")
{
    using namespace std::chrono;

    jed_utils::datetime date1{ 2024, 4, 11 };
    jed_utils::datetime date2{ 2024, 4, 11 };
    Pay pay{};
    Receptionist receptionist1{"name1", "id", pay};
    Receptionist receptionist2{"name2", "id", pay};
    TimetableEntry entry1{receptionist1, date1, Shift::II};
    TimetableEntry entry2{receptionist2, date2, Shift::II};
    REQUIRE( entry1 == entry2 );
    TimetableEntry entry3 = entry1;
    REQUIRE( entry1 == entry3 );
}

