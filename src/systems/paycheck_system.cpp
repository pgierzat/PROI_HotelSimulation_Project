#include "paycheck_system.hpp"


void PaycheckSystem::bind_worker_system(WorkerSystem& wsystem) { worker_system = &wsystem; }

void PaycheckSystem::close_month()
{
    worker_system -> reset_stats();
}

std::vector<Paycheck> PaycheckSystem::calculate_paychecks()
{
    std::vector<Paycheck> paychecks{};
    for (const Worker* worker : worker_system -> get_workers())
    {
        unsigned hours_worked = 0;  // calculate it
        paychecks.emplace_back(*worker, worker -> calculate_paycheck(hours_worked));
    }
    return paychecks;
}
