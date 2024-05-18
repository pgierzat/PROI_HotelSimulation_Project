#include <algorithm>
#include "big_task.hpp"
#include "../utilities/errors.hpp"

BigTask::BigTask(const std::string& id, const std::string& description, unsigned workers_required) :
    Task{id, description}, required{workers_required}
{
    if (workers_required == 0)
        throw std::invalid_argument("workers required cannot be 0.");
}

unsigned BigTask::get_required() const noexcept { return required; }

unsigned BigTask::get_assigned() const noexcept { return assigned; }

void BigTask::can_assign(const Worker& worker) const
{
    Task::can_assign(worker);
    if (assigned >= required)
        throw TaskCapacityError("Tried to assign too many workers to a task.", *this, worker);
    auto workers = get_workers();
    auto p = std::ranges::find_if(workers,
        [&](const Worker* otr_worker){ return *otr_worker == worker; }  );
    if (p != workers.end())
        throw DuplicateWorkerIDError("Tried to assign same worker to a task twice", worker);
}
