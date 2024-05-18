#include "catch_amalgamated.hpp"
#include "../src/tasks/bring_dish_task.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test BringDishTask")
{
    Table table{"25"};
    BringDishTask bringtask{"1111", Dish::Omelette, table};
    Task& task = bringtask;

    SECTION("init")
    {
        REQUIRE(task.get_description() == "Bring a dish to a table.");
        REQUIRE(bringtask.get_dish() == Dish::Omelette);
        REQUIRE(bringtask.get_table() == table);
    }
}
