#include "catch_amalgamated.hpp"
#include "../src/json_converters/JSON_worker.hpp"
#include "../src/workers/receptionist.hpp"
#include "../src/workers/cook.hpp"


TEST_CASE("Test JSONWorker")
{
    SECTION("correct use")
    {
        auto pay = Pay{PaycheckMethod::Wage, Amount{24, 3}};
        auto receptionist = Receptionist{"id", "name", pay};
        auto j = JSONWorker::write(receptionist);
        auto read_receptionist = JSONWorker::read<Receptionist>(j);
        REQUIRE( receptionist == read_receptionist );
    }

    SECTION("mistaken worker type")
    {
        auto pay = Pay{PaycheckMethod::Wage, Amount{24, 3}};
        auto receptionist = Receptionist{"id", "name", pay};
        auto j = JSONWorker::write(receptionist);
        auto read_cook = Cook{};
        REQUIRE_NOTHROW( read_cook = JSONWorker::read<Cook>(j) );
        REQUIRE( receptionist == read_cook );
    }
}
