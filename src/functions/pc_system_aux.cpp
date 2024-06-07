#include "pc_system_aux.hpp"


PaycheckSameWorkerID::PaycheckSameWorkerID(const Paycheck& paycheck) : id{paycheck.get_worker_id()} {}

PaycheckSameWorkerID::PaycheckSameWorkerID(const std::string& id) : id{id} {}

bool PaycheckSameWorkerID::operator()(const Paycheck& otr_paycheck)
{
    return otr_paycheck.get_worker_id() == id;
}
