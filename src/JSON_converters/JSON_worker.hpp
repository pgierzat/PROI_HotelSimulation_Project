#ifndef JSON_WORKER_HPP
#define JSON_WORKER_HPP

#include "../utilities/json.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/concepts.hpp"
#include "../workers/cook.hpp"
#include "../workers/maid.hpp"
#include "../workers/receptionist.hpp"
#include "../workers/waiter.hpp"
#include "JSON_pay.hpp"
#include <memory>

class JSONWorker
{
    using json = nlohmann::json;
    public:
        static json write(const Worker&);
        template<SupportedWorker T>
            static T read_specific(const json&);
        static std::unique_ptr<Worker> read(const json&);
    private:
        template<SupportedWorker T>
            static T unchecked_read_specific(const json&);
        static WorkerType get_type(const json&);
};


template<SupportedWorker T>
T JSONWorker::read_specific(const json& j)
{
    auto type = get_type(j);
    if (type != T::type)
        throw IncorrectWorkerType(
            "Worker parsed from JSON has another type than expected",
            T::type, type
        );
    return unchecked_read_specific<T>(j);
}

template<SupportedWorker T>
T JSONWorker::unchecked_read_specific(const json& j)
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


#endif
