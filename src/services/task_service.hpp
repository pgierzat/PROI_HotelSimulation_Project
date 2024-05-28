#ifndef TASK_STATE_HPP
#define TASK_STATE_HPP

#include "service.hpp"
#include "../systems/service_system.hpp"

class TaskSystem;

class TaskService : public Service
{
    protected:
        TaskService(const std::string& id, const Guest& requestee);
        static TaskSystem* t_system;
    public:
        ServiceStatus refresh_status(const ServiceSystem&) noexcept override;
        virtual std::vector<const Task*> get_tasks() const = 0;
        virtual const std::string& get_description() const noexcept override = 0;
        virtual Amount get_default_price() const noexcept override = 0;
        virtual void add_to_systems(ServiceSystem&) override = 0;
        static void set_t_system(TaskSystem&);
};

#endif
