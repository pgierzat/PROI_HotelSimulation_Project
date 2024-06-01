#ifndef JSON_AMOUNT_HPP
#define JSON_AMOUNT_HPP

#include "../utilities/json.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/concepts.hpp"
#include "../types/amount.hpp"

namespace JSONAmount
{
    using nlohmann::json;
    json write(const Amount&);
    Amount read(const json&);
}

#endif
