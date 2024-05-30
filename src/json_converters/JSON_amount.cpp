#include "JSON_amount.hpp"
#include <regex>
#include <string>
#include <sstream>
#include <iomanip>

namespace JSONAmount
{
    json write(const Amount& amount)
    {
        auto formatted = std::stringstream{};
        auto dollars = std::to_string(amount.get_dollars());
        auto cents = std::to_string(amount.get_cents());
        formatted << dollars << '.' << std::setfill('0') << std::setw(2) << cents;
        return formatted.str();
    }

    Amount read(const json& j)
    {
        try
        {
            auto pat = std::regex{R"((\d+)\.(\d{2}))"};
            auto matches = std::smatch{};
            auto data_str = j.get<std::string>();
            int dollars, cents;
            if (std::regex_match(data_str, matches, pat)) {
                dollars = std::stoi(matches[1]);
                cents = std::stoi(matches[2]);
            } else {
                throw JSONInvalidData("Amount doesn't match the N+.NN format.", j);
            }
            return Amount{dollars, cents};
        } catch(const json::exception& e) {
            throw JSONException("Error parsing Amount", j);
        } catch(const std::invalid_argument& e) {
            throw JSONInvalidData("Error parsing Amount", j);
        }
}
}
