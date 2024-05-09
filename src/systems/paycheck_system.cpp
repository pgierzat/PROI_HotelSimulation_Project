#include "paycheck_system.hpp"


void PaycheckSystem::bind_worker_system(WorkerSystem& wsystem) { worker_system = &wsystem; }

void PaycheckSystem::close_month()
{
    worker_system -> reset_hours_worked();
    worker_system -> reset_stats();
}

std::vector<Paycheck> PaycheckSystem::calculate_paychecks()
{
    std::vector<Paycheck> paychecks{};
    for (const Worker* worker : worker_system -> get_workers())
        paychecks.emplace_back(*worker, worker -> calculate_paycheck());
    return paychecks;
}
