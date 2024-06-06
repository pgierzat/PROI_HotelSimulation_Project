#include <algorithm>
#include <optional>
#include <concepts>
#include "worker_system.hpp"

WorkerSystem::WorkerSystem(std::vector<std::unique_ptr<Worker>> workers) : workers(std::move(workers)) {}

WorkerSystem::WorkerSystem(std::vector<std::unique_ptr<Worker>> workers) : workers(std::move(workers)) {}

std::optional<const Worker*> WorkerSystem::find_by_id(std::string id) const noexcept
{
    auto p = std::ranges::find_if(workers, [&](const auto& worker){ return worker -> get_id() == id; });
    if (p == workers.end())
        return std::nullopt;
    return p -> get();
}

const Worker& WorkerSystem::get_by_id(std::string id) const
{
    auto p = std::ranges::find_if(workers, [&](const auto& worker){ return worker -> get_id() == id; });
    if (p == workers.end())
        throw WorkerNotInSystemError("WorkerSystem::get_by_id failed", id);
    return **p;
}

std::vector<const Worker*> WorkerSystem::get_workers() const
{
    std::vector<const Worker*> vec{};
    std::ranges::for_each(workers, [&](const std::unique_ptr<Worker>& pw){ vec.push_back(pw.get()); });
    return vec;
}

void WorkerSystem::set_dishes_prepared(const Cook& cook, unsigned dishes_prepared)
{
    Cook& cook_ref = validate_and_cast(cook);
    cook_ref.set_dishes_prepared(dishes_prepared);
}

void WorkerSystem::set_rooms_serviced(const Maid& maid, unsigned rooms_serviced)
{
    Maid& maid_ref = validate_and_cast(maid);
    maid_ref.set_rooms_serviced(rooms_serviced);
}

void WorkerSystem::set_complaints(const Receptionist& receptionist, unsigned complaints)
{
    Receptionist& receptionist_ref = validate_and_cast(receptionist);
    receptionist_ref.set_complaints(complaints);
}

void WorkerSystem::set_orders_taken(const Waiter& waiter, unsigned orders_taken)
{
    Waiter& waiter_ref = validate_and_cast(waiter);
    waiter_ref.set_orders_taken(orders_taken);
}

void WorkerSystem::reset_stats()
{
    for (const std::unique_ptr<Worker>& worker : workers)
        worker -> reset_stats();
}

Worker& WorkerSystem::validate_worker(const Worker& worker)
{
    auto p = std::ranges::find_if(workers, [&](const auto& otr_worker){ return *otr_worker == worker; });
    if (p == workers.end())
        throw WorkerNotInSystemError("Unsuccesfull worker validation", worker);
    return **p;
}
