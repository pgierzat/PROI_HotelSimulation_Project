#include "catch_amalgamated.hpp"
#include "../src/types/datetime.h"
#include "../src/types/timetable_entry.hpp"
#include "../src/workers/receptionist.hpp"
#include "../src/workers/maid.hpp"


TEST_CASE("Test TimetableEntry")
{
    jed_utils::datetime date{ 2024, 4, 11 };
    Pay pay{PaycheckMethod::Salary, Amount{0, 0}};
    Receptionist receptionist{"name", "id", pay};

    SECTION("init")
    {
        jed_utils::datetime date_long{ 2024, 4, 11, 2, 32, 55};
        jed_utils::datetime expected_start{ 2024, 4, 11, 22};
        jed_utils::datetime expected_end{ 2024, 4, 12, 6};
        TimetableEntry entry{receptionist, date_long, Shift::III};
        REQUIRE( entry.get_date() == date );
        REQUIRE( entry.get_worker() == receptionist );
        REQUIRE( entry.get_shift() == Shift::III );
        TimeInterval expected_interval{expected_start, expected_end};
        REQUIRE( entry.get_interval() == expected_interval );
    }

    SECTION("init, invalid, wrong shift")
    {
        Maid maid{"name", "id", pay};
        // maids work 2 shifts
        REQUIRE_THROWS( TimetableEntry{maid, date, Shift::III} );
    }

    SECTION("opearator ==")
    {
        jed_utils::datetime date1{ 2024, 4, 11 };
        jed_utils::datetime date2{ 2024, 4, 11 };
        Pay pay{PaycheckMethod::Salary, Amount{0, 0}};
        Receptionist receptionist1{"name1", "id", pay};
        Receptionist receptionist2{"name1", "id", pay};
        TimetableEntry entry1{receptionist1, date1, Shift::II};
        TimetableEntry entry2{receptionist2, date2, Shift::II};
        REQUIRE( entry1 == entry2 );
        TimetableEntry entry3 = entry1;
        REQUIRE( entry1 == entry3 );
    }
}
