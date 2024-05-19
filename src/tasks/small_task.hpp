#ifndef SMALL_TASK_HPP
#define SMALL_TASK_HPP

#include "task.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/concepts.hpp"

template<SupportedWorker T>
class SmallTask : public Task
{
    protected:
        SmallTask(const std::string& id, const std::string& description);
        const T* assignee = nullptr;
    public:
        const T& get_assignee() const;
        void assign(const T&);
        void assign(const Worker&) override;
        void unassign() override;
};


template<SupportedWorker T>
SmallTask<T>::SmallTask(const std::string& id, const std::string& description) :
    Task{id, description} {}

template<SupportedWorker T>
const T& SmallTask<T>::get_assignee() const
{
    if (not assignee)
        throw TaskStatusError("Tried to get the assignee of an unassigned task.", *this);
    return *assignee;
}

template<SupportedWorker T>
void SmallTask<T>::assign(const T& worker)
{
    can_assign(worker);
    status = TaskStatus::assigned;
    assignee = &worker;
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
    assignee = nullptr;
    status = TaskStatus::unassigned;
}


#endif
