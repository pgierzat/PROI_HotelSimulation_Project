#include "catch_amalgamated.hpp"
#include "../src/tasks/prepare_dish_task.hpp"
#include "../src/utilities/errors.hpp"


TEST_CASE("Test Task")
{
    PrepareDishTask preptask{"1111", Dish::Omelette};
    Task& task = preptask;

    SECTION("init")
    {
        REQUIRE(task.get_description() == "Prepare a dish.");
        REQUIRE(task.get_id() == "1111");
        REQUIRE(task.get_status() == TaskStatus::unassigned);
    }

    SECTION("completion before assignment")
    {
        REQUIRE_THROWS_AS(task.mark_completed(), TaskStatusError);
    }
}
