#ifndef JSON_WORKER_HPP
#define JSON_WORKER_HPP

#include "../utilities/json.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/concepts.hpp"
#include "../workers/worker.hpp"
#include "JSON_pay.hpp"

namespace JSONWorker
{
    using nlohmann::json;
    json write(const Worker&);
    template<SupportedWorker T>
        T read(const json&);
}

namespace JSONWorker
{
    template<SupportedWorker T>
    T read(const json& j)
    {
        try
        {
            std::string id = j.at("id");
            std::string name = j.at("name");
            const json& pay_data = j.at("pay");
            Pay pay = JSONPay::read(pay_data);
            return T{id, name, pay};
        } catch(const json::exception& e) {
            throw JSONException("Error parsing Worker", j);
        } catch(const std::invalid_argument& e) {
            throw JSONInvalidData("Error parsing Worker", j);
        }
    }
}

#endif
