#include "JSON_worker.hpp"
#include "JSON_pay.hpp"

namespace JSONWorker
{
    json write(const Worker& worker)
    {
        json pay_data = JSONPay::write(worker.get_pay());
        return {
            {"id", worker.get_id()},
            {"name", worker.get_name()},
            {"type", Worker::wtype_to_str(worker.get_type())},
            {"pay", pay_data}
        };
    }

    std::unique_ptr<Worker> read_unspecific(const json& j)
    {
        try
        {
            std::string type_str = j.at("type");
            WorkerType type = Worker::str_to_wtype(type_str);
            switch (type)
            {
            case WorkerType::Cook:
                return std::make_unique<Cook>(read<Cook>(j));
            case WorkerType::Maid:
                return std::make_unique<Maid>(read<Maid>(j));
            case WorkerType::Receptionist:
                return std::make_unique<Receptionist>(read<Receptionist>(j));
            case WorkerType::Waiter:
                return std::make_unique<Waiter>(read<Waiter>(j));
            default:
                throw UnsupportedWorkerTypeError("Tried to read invalid Worker from json.", type);
            }
        } catch(const json::exception& e) {
            throw JSONException("Error parsing Worker", j);
        } catch(const std::invalid_argument& e) {
            throw JSONInvalidData("Error parsing Worker", j);
        }
    }
}
