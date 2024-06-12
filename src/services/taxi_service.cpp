#include "taxi_service.hpp"
#include "../systems/task_system.hpp"
#include "../systems/service_system.hpp"


const std::string TaxiService::description = "Order a taxi for a guest.";

TaxiService::TaxiService(const std::string& id, const Guest& requestee, const jed_utils::datetime& time) :
    TaskService{id, requestee}, time{time} {}

void TaxiService::add_to_systems(ServiceSystem& sc_system)
{
    if (added == ServiceAdded::added)
        throw ServiceStatusError("Tried to add service to systems twice.", *this);
    auto& t_system = sc_system.get_t_system();
    auto& task = t_system.add_task_id(TaxiTask("", get_requestee(), time));
    TasksObs::add_observed(task);
}

const std::string& TaxiService::get_description() const noexcept { return description; }

const TaxiTask& TaxiService::get_taxitask() const
{
    return dynamic_cast<const TaxiTask&>(TasksObs::front());
}

Amount TaxiService::get_default_price() const noexcept { return Amount{0, 0}; }
