#include "JSON_worker.hpp"
#include "JSON_pay.hpp"


nlohmann::json JSONWorker::write(const Worker& worker)
{
    json pay_data = JSONPay::write(worker.get_pay());
    return {
        {"id", worker.get_id()},
        {"name", worker.get_name()},
        {"type", Worker::wtype_to_str(worker.get_type())},
        {"pay", pay_data}
    };
}

std::unique_ptr<Worker> JSONWorker::read(const json& j)
{
    try
    {
        auto type = get_type(j);
        switch (type)
        {
        case WorkerType::Cook:
            return std::make_unique<Cook>(unchecked_read_specific<Cook>(j));
        case WorkerType::Maid:
            return std::make_unique<Maid>(unchecked_read_specific<Maid>(j));
        case WorkerType::Receptionist:
            return std::make_unique<Receptionist>(unchecked_read_specific<Receptionist>(j));
        case WorkerType::Waiter:
            return std::make_unique<Waiter>(unchecked_read_specific<Waiter>(j));
        default:
            throw UnsupportedWorkerTypeError("Tried to read a Worker of unknown type from json.", type);
        }
    } catch(const json::exception& e) {
        throw JSONException("Error parsing Worker", j);
    } catch(const std::invalid_argument& e) {
        throw JSONInvalidData("Error parsing Worker", j);
    }
}

WorkerType JSONWorker::get_type(const json& j)
{
    auto type_str = std::string{};
    try {
        type_str = j.at("type");
    } catch(const json::exception& e) {
        throw JSONException("Error parsing Worker's type", j);
    }
    return Worker::str_to_wtype(type_str);
}
