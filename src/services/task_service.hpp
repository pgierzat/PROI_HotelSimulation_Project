#ifndef TASK_STATE_HPP
#define TASK_STATE_HPP

#include "service.hpp"
#include "../auxiliary/multiple_own_system_observer.hpp"
#include "../systems/service_system.hpp"

class TaskSystem;

class TaskService : public Service, public MultipleOwnSystemObserver<Task>
{
        using TasksObs = MultipleOwnSystemObserver<Task>;
    protected:
        TaskService(const std::string& id, const Guest& requestee);
        void add_to_systems(ServiceSystem&) override;
    public:
        virtual std::vector<const Task*> get_tasks() const;
};

#endif
