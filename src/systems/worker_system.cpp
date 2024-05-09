#include <algorithm>
#include <optional>
#include <concepts>
#include "worker_system.hpp"


std::optional<const Worker*> WorkerSystem::find_by_id(std::string id) const noexcept
{
    auto worker_opt = get_by_id(id);
    std::optional<const Worker*> c_worker_opt = std::nullopt;
    if (worker_opt)
        c_worker_opt = worker_opt.value();
    return c_worker_opt;
}

std::vector<const Worker*> WorkerSystem::get_workers() const
{
    std::vector<const Worker*> vec{};
    std::ranges::for_each(workers, [&](const std::unique_ptr<Worker>& pw){ vec.push_back(pw.get()); });
    return vec;
}

void WorkerSystem::set_hours_worked(std::string id, unsigned hours_worked)
{
    auto worker = check_id(id);
    worker -> set_hours_worked(hours_worked);
}

void WorkerSystem::set_dishes_prepared(std::string id, unsigned dishes_prepared)
{
    auto& cook = *cast_worker<Cook>(check_id(id));
    cook.set_dishes_prepared(dishes_prepared);
}

void WorkerSystem::set_rooms_serviced(std::string id, unsigned rooms_serviced)
{
    auto& maid = *cast_worker<Maid>(check_id(id));
    maid.set_rooms_serviced(rooms_serviced);
}

void WorkerSystem::set_complaints(std::string id, unsigned complaints)
{
    auto& receptionist = *cast_worker<Receptionist>(check_id(id));
    receptionist.set_complaints(complaints);
}

void WorkerSystem::set_orders_taken(std::string id, unsigned orders_taken)
{
    auto& waiter = *cast_worker<Waiter>(check_id(id));
    waiter.set_orders_taken(orders_taken);
}

void WorkerSystem::reset_hours_worked()
{
    for (const std::unique_ptr<Worker>& worker : workers)
        worker -> set_hours_worked(0);
}

void WorkerSystem::reset_stats()
{
    for (const std::unique_ptr<Worker>& worker : workers)
        worker -> reset_stats();
}

std::optional<Worker*> WorkerSystem::get_by_id(std::string id) const noexcept
{
    auto p = std::ranges::find_if(workers, [&id](const std::unique_ptr<Worker>& pw){ return pw -> get_id() == id; });
    if ( p == workers.end() )
        return std::nullopt;
    return &**p;
}

Worker* WorkerSystem::check_id(std::string id) const
{
    auto worker = get_by_id(id).value_or(nullptr);
    if (!worker)
        throw IDNotFoundError("ID not found", id);
    return worker;
}
