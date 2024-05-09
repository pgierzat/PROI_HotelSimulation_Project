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
        void set_hours_worked(std::string id, unsigned hours_worked);
        void set_dishes_prepared(std::string id, unsigned dishes_prepared);
        void set_rooms_serviced(std::string id, unsigned rooms_serviced);
        void set_complaints(std::string id, unsigned complaints);
        void set_orders_taken(std::string id, unsigned orders_taken);
        void reset_hours_worked();
        void reset_stats();
        template <SupportedWorker T>
            static T* cast_worker(Worker*);
    private:
        std::optional<Worker*> get_by_id(std::string id) const noexcept;
        Worker* check_id(std::string id) const;
        std::vector<std::unique_ptr<Worker>> workers;
};


template<SupportedWorker T>
void WorkerSystem::add_worker(const T& worker)
{
    if (worker.get_name().empty() || worker.get_id().empty() ||
            worker.get_paycheck_method() == PaycheckMethod::NoneType)
        throw InvalidWorkerError("Cannot add worker", worker);
    if ( find_by_id(worker.get_id()) )
        throw DuplicateWorkerIDError("Cannot add worker", worker);
    auto p = std::make_unique<T>(worker);
    workers.push_back(std::move(p));
}

template <SupportedWorker T>
T* WorkerSystem::cast_worker(Worker* worker)
{
    T* specific_worker = nullptr;
    try {
        specific_worker = dynamic_cast<T*>(worker);
    }
    catch (const std::bad_cast& e) {
        throw IncorrectWorkerType("Attempted to make an incorrect cast", *worker, T::type);
    }
    return specific_worker;
}

#endif
