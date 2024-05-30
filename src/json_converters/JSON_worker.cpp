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
            {"pay", pay_data}
        };
    }
}
