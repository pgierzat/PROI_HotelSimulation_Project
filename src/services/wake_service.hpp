#ifndef WAKE_SERVICE_HPP
#define WAKE_SERVICE_HPP

#include "task_service.hpp"
#include "../tasks/wake_task.hpp"
#include "../systems/service_system.hpp"

class WakeService : public TaskService
{
    public:
        WakeService(const std::string& id, const Guest&, const jed_utils::datetime&);
        void add_to_systems(ServiceSystem&) override;
        const std::string& get_description() const noexcept override;
        std::vector<const Task*> get_tasks() const override;
        const WakeTask& get_waketask() const;
        Amount get_default_price() const noexcept;
    private:
        static const std::string description;
        jed_utils::datetime time;
        std::string waketask_id;
};
#endif