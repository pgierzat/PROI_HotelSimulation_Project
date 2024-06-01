#ifndef JSON_PAY_HPP
#define JSON_PAY_HPP

#include "../utilities/json.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/concepts.hpp"
#include "../types/pay.hpp"

namespace JSONPay
{
    using nlohmann::json;
    json write(const Pay&);
    Pay read(const json&);
}

#endif
