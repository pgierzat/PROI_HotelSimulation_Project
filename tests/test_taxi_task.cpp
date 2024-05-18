#include "catch_amalgamated.hpp"
#include "../src/tasks/taxi_task.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test TaxiTask")
{
    Guest guest{"name1"};
    jed_utils::datetime time{2024, 5, 18, 6, 45};
    TaxiTask taxitask{"1111", guest, time};
    Task& task = taxitask;

    SECTION("init")
    {
        REQUIRE(task.get_description() == "Order a taxi for a guest.");
        REQUIRE(taxitask.get_guest() == guest);
        REQUIRE(taxitask.get_time() == time);
    }
}
