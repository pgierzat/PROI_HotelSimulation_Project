#include "catch_amalgamated.hpp"
#include "../src/auxiliary/own_system_observer.hpp"
#include "../src/utilities/errors.hpp"
#include "../src/workers/cook.hpp"
#include "../src/workers/maid.hpp"

TEST_CASE("Test OwnSystemObserver")
{
    auto cook = Cook{"id1", "name1", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
    auto observer = OwnSystemObserver<Worker>(cook);

    SECTION("Test init")
    {
        REQUIRE( observer.get() == cook );
        REQUIRE( observer.get_observed_id() == "id1" );
    }

    SECTION("Test default init")
    {
        auto observer = OwnSystemObserver<Worker>();
        REQUIRE_THROWS_AS( observer.get() ,  OwnSystemObserverError<Worker> );
        REQUIRE( observer.get_observed_id() == "" );
    }

    SECTION("Test set")
    {
        auto maid = Maid{"id2", "name2", Pay{PaycheckMethod::Salary, Amount{3200, 0}}};
        observer.set(maid);
        REQUIRE( observer.get() == maid );
        REQUIRE( observer.get_observed_id() == "id2" );
    }

    SECTION("Test notify erase")
    {
        observer.notify_erase();
        REQUIRE_THROWS_AS( observer.get(),  OwnSystemObserverError<Worker> );
        REQUIRE( observer.get_observed_id() == "id1" );
    }

    SECTION("Test notify realloc")
    {
        auto cook2 = cook;
        cook2.set_name("othername");
        observer.notify_realloc(cook2);
        REQUIRE( observer.get() == cook2 );
        REQUIRE( observer.get_observed_id() == "id1" );
    }

    SECTION("Test notify realloc, wrong id")
    {
        auto cook2 = cook;
        cook2.set_id("otherid");
        REQUIRE_THROWS_AS( observer.notify_realloc(cook2), OwnSystemObserverError<Worker> );
    }
}
