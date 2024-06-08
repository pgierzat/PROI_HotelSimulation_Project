#ifndef BIG_TASK_HPP
#define BIG_TASK_HPP

#include <vector>
#include <algorithm>
#include "task.hpp"
#include "../auxiliary/multiple_own_system_observer.hpp"
#include "../systems/task_system.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/concepts.hpp"

template<SupportedWorker T>
class BigTask : public Task, protected MultipleOwnSystemObserver<Worker>
{
    protected:
            using MOSO = MultipleOwnSystemObserver<Worker>;
        BigTask(const std::string& id, const std::string& description, unsigned workers_required);
        virtual void can_assign(const Worker&) const override;
        unsigned required;
        unsigned assigned = 0;
    public:
        void assign(const T&);
        void assign(const Worker&) override;
        void unassign() override;
        std::vector<const T*> get_assignees() const noexcept;
        unsigned get_required() const noexcept;
        unsigned get_assigned() const noexcept;
};


template<SupportedWorker T>
BigTask<T>::BigTask(const std::string& id, const std::string& description, unsigned workers_required) :
    Task{id, description}, MOSO{}, required{workers_required}
{
    if (workers_required == 0)
        throw std::invalid_argument("workers required cannot be 0.");
}

template<SupportedWorker T>
unsigned BigTask<T>::get_required() const noexcept { return required; }

template<SupportedWorker T>
unsigned BigTask<T>::get_assigned() const noexcept { return assigned; }

template<SupportedWorker T>
void BigTask<T>::assign(const T& worker)
{
    can_assign(worker);
    if (++assigned == required)
        status = TaskStatus::assigned;
    MOSO::add_observed(worker);
}

template<SupportedWorker T>
void BigTask<T>::assign(const Worker& worker)
{
    auto cast = dynamic_cast<const T*>(&worker);
    if (not cast)
        throw TaskAssignmentError("Tried to assign worker of incorrect type", *this, worker);
    assign(*cast);
} 

template<SupportedWorker T>
void BigTask<T>::unassign() {
    can_unassign();
    MOSO::remove_all_observed();
    status = TaskStatus::unassigned;
}

template<SupportedWorker T>
std::vector<const T*> BigTask<T>::get_assignees() const noexcept
{
    std::vector<const T*> specific_assignees;
    auto assignees = MOSO::get();
    for (auto assignee : assignees)
        specific_assignees.push_back(dynamic_cast<const T*>(assignee));
    return specific_assignees;
}

template<SupportedWorker T>
void BigTask<T>::can_assign(const Worker& worker) const
{
    Task::can_assign(worker);
    if (assigned >= required)
        throw TaskCapacityError("Tried to assign too many workers to a task.", *this, worker);
    if (MOSO::has_id(worker.get_id()))
        throw DuplicateWorkerIDError("Tried to assign same worker to a task twice", worker);
}

#endif
