#include "taxi_service.hpp"
#include "../systems/task_system.hpp"
#include "../systems/service_system.hpp"


const std::string TaxiService::description = "Order a taxi for a guest.";

TaxiService::TaxiService(const std::string& id, const Guest& requestee, const jed_utils::datetime& time) :
    TaskService{id, requestee}, time{time} {}

void TaxiService::add_to_systems(ServiceSystem& sc_system)
{
    const auto& requestee = g_system -> get_by_id(requestee_id);
    t_system -> add_task(TaxiTask(id, requestee, time));   // need id generator
    taxitask_id  = id;
}

const std::string& TaxiService::get_description() const noexcept { return description; }

const TaxiTask& TaxiService::get_taxitask() const
{
    return dynamic_cast<const TaxiTask&>(t_system -> get_by_id(taxitask_id));
}

std::vector<const Task*> TaxiService::get_tasks() const
{
    return std::vector<const Task*>{&get_taxitask()};
}

Amount TaxiService::get_default_price() const noexcept { return Amount{0, 0}; }
