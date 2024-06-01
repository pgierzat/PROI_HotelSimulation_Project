#include "catch_amalgamated.hpp"
#include "../src/JSON_converters/JSON_worker.hpp"
#include "../src/workers/receptionist.hpp"
#include "../src/workers/cook.hpp"


TEST_CASE("Test JSONWorker")
{
    SECTION("correct use of read_specific")
    {
        auto pay = Pay{PaycheckMethod::Wage, Amount{24, 3}};
        auto receptionist = Receptionist{"id", "name", pay};
        auto j = JSONWorker::write(receptionist);
        auto read_receptionist = JSONWorker::read_specific<Receptionist>(j);
        REQUIRE( receptionist == read_receptionist );
    }

    SECTION("mistaken worker type")
    {
        auto pay = Pay{PaycheckMethod::Wage, Amount{24, 3}};
        auto receptionist = Receptionist{"id", "name", pay};
        auto j = JSONWorker::write(receptionist);
        REQUIRE_THROWS_AS( JSONWorker::read_specific<Cook>(j), IncorrectWorkerType);
    }

    SECTION("read, unspecific")
    {
        auto pay = Pay{PaycheckMethod::Wage, Amount{24, 3}};
        auto receptionist = Receptionist{"id", "name", pay};
        auto j = JSONWorker::write(receptionist);
        auto ptr = JSONWorker::read(j);
        auto read_receptionist = dynamic_cast<Receptionist&>(*ptr);
        REQUIRE( receptionist == read_receptionist );
    }
}
