#include "catch_amalgamated.hpp"
#include "../src/json_converters/JSON_pay.hpp"


TEST_CASE("Test JSONPay")
{
    auto pay = Pay{PaycheckMethod::Wage, Amount{24, 3}};
    auto j = JSONPay::write(pay);
    auto read_pay = JSONPay::read(j);
    REQUIRE( pay == read_pay );
}
