#include "catch_amalgamated.hpp"
#include "../src/auxiliary/multiple_own_system_observer.hpp"
#include "../src/utilities/errors.hpp"
#include "../src/functions/equal_operators.hpp"
#include "../src/workers/cook.hpp"
#include "../src/workers/maid.hpp"

TEST_CASE("Test MultipleOwnSystemObserver")
{
    auto cook = Cook{"id1", "name1", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
    auto maid = Maid{"id2", "name2", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
    auto observer = MultipleOwnSystemObserver<Worker>();

    SECTION("Test init")
    {
        REQUIRE( observer.get().empty() );
        REQUIRE( observer.get_ids().empty() );
        REQUIRE( observer.size() == 0 );
    }

    SECTION("Test add")
    {
        observer.add_observed(cook);
        observer.add_observed(maid);
        std::vector<const Worker*> exp{&cook, &maid};
        REQUIRE( observer.get() == exp );
        auto exp_ids = std::vector<std::string>{"id1", "id2"};
        REQUIRE( observer.get_ids() == exp_ids );
        REQUIRE( observer.size() == 0 );
    }

    SECTION("Test notify erase")
    {
        observer.notify_erase();
        REQUIRE_THROWS_AS( observer.get(),  OwnSystemObserverError<Worker> );
        REQUIRE( observer.get_id() == "" );
    }

    SECTION("Test notify realloc")
    {
        auto cook2 = cook;
        cook2.set_name("othername");
        observer.notify_realloc(cook2);
        REQUIRE( observer.get() == cook );
        REQUIRE( observer.get_id() == "id1" );
    }

    SECTION("Test notify realloc, wrong id")
    {
        auto cook2 = cook;
        cook2.set_id("otherid");
        REQUIRE_THROWS_AS( observer.notify_realloc(cook2), OwnSystemObserverError<Worker> );
    }
}
