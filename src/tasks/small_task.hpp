#ifndef SMALL_TASK_HPP
#define SMALL_TASK_HPP

#include "task.hpp"
#include "../auxiliary/own_system_observer.hpp"
#include "../auxiliary/pseudo_multiple_own_system_observer.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/concepts.hpp"

template<SupportedWorker T>
class SmallTask :
    public Task,
    protected OwnSystemObserver<Worker>,
    protected PseudoMultipleOwnSystemObserver<Worker>
{
    protected:
        using WorkerObs = OwnSystemObserver<Worker>;    
        SmallTask(const std::string& id, const std::string& description);
    public:
        const T& get_assignee() const;
        void assign(const T&);
        void assign(const Worker&) override;
        void unassign() override;
};


template<SupportedWorker T>
SmallTask<T>::SmallTask(const std::string& id, const std::string& description) :
    Task{id, description}, OwnSystemObserver<Worker>{} {}

template<SupportedWorker T>
const T& SmallTask<T>::get_assignee() const
{
    if (not WorkerObs::has_value())
        throw TaskStatusError("Tried to get assignee of an unassigned task.", *this);
    return dynamic_cast<const T&>(WorkerObs::get());
}

template<SupportedWorker T>
void SmallTask<T>::assign(const T& worker)
{
    can_assign(worker);
    status = TaskStatus::assigned;
    WorkerObs::set(worker);
}

template<SupportedWorker T>
void SmallTask<T>::assign(const Worker& worker)
{
    auto cast = dynamic_cast<const T*>(&worker);
    if (not cast)
        throw TaskAssignmentError("Tried to assign worker of incorrect type", *this, worker);
    assign(*cast);
} 

template<SupportedWorker T>
void SmallTask<T>::unassign()
{
    can_unassign();
    WorkerObs::reset();
    status = TaskStatus::unassigned;
}


#endif
