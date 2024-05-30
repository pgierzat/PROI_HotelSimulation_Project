#include "JSON_pay.hpp"
#include "JSON_amount.hpp"

namespace JSONPay
{
    json write(const Pay& pay)
    {
        auto method_data = Pay::method_to_str(pay.get_method());
        auto amount_data = JSONAmount::write(pay.get_amount());
        return {
            {"method", method_data},
            {"amount", amount_data}
        };
    }

    Pay read(const json& j)
    {
    try
    {
        const std::string& method_data = j.at("method");
        PaycheckMethod method = Pay::method_from_str(method_data);
        auto amount_data = j.at("amount");
        auto amount = JSONAmount::read(amount_data);
        return Pay{method, amount};
    } catch(const json::exception& e) {
        throw JSONException("Error parsing Pay", j);
    } catch(const std::invalid_argument& e) {
        throw JSONInvalidData("Error parsing Pay", j);
    }
}
}
