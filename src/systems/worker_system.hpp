#include <memory>
#include <vector>
#include <optional>
#include "../workers/worker.hpp"
#include "../workers/cook.hpp"
#include "../workers/maid.hpp"
#include "../workers/receptionist.hpp"
#include "../workers/waiter.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/concepts.hpp"


#ifndef WORKER_SYSTEM_HPP
#define WORKER_SYSTEM_HPP

class WorkerSystem
{
    public:
        WorkerSystem() = default;
        WorkerSystem(const WorkerSystem&) = delete;
        WorkerSystem(WorkerSystem&&) = delete;
        WorkerSystem& operator=(const WorkerSystem&) = delete;
        WorkerSystem& operator=(WorkerSystem&&) = delete;
        template<SupportedWorker T>
            void add_worker(const T&);
        std::optional<const Worker*> find_by_id(std::string id) const noexcept;
        std::vector<const Worker*> get_workers() const;
        void set_hours_worked(const Worker&, unsigned hours_worked);
        void set_dishes_prepared(const Cook&, unsigned dishes_prepared);
        void set_rooms_serviced(const Maid&, unsigned rooms_serviced);
        void set_complaints(const Receptionist&, unsigned complaints);
        void set_orders_taken(const Waiter&, unsigned orders_taken);
        void reset_hours_worked();
        void reset_stats();
    private:
        Worker& validate_worker(const Worker&);
        template <SupportedWorker T>
            T& validate_and_cast(const T&);
        std::vector<std::unique_ptr<Worker>> workers;
};


template<SupportedWorker T>
void WorkerSystem::add_worker(const T& worker)
{
    if (worker.get_name().empty() || worker.get_id().empty())
        throw InvalidWorkerError("Cannot add worker", worker);
    if ( find_by_id(worker.get_id()) )
        throw DuplicateWorkerIDError("Cannot add worker", worker);
    auto p = std::make_unique<T>(worker);
    workers.push_back(std::move(p));
}

template <SupportedWorker T>
T& WorkerSystem::validate_and_cast(const T& worker)
{
    auto& worker_ref = validate_worker(worker);
    return dynamic_cast<T&>(worker_ref);
}

#endif
