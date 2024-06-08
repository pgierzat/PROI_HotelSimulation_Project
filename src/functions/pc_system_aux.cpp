#include "pc_system_aux.hpp"
#include "../workers/worker.hpp"

PaycheckSameWorkerID::PaycheckSameWorkerID(const Paycheck& paycheck) : id{paycheck.get_worker().get_id()} {}

PaycheckSameWorkerID::PaycheckSameWorkerID(const std::string& id) : id{id} {}

bool PaycheckSameWorkerID::operator()(const InnerPaycheck& otr_paycheck)
{
    return otr_paycheck.get_cworker_observer().get_id() == id;
}
