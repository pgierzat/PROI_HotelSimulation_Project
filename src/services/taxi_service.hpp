#ifndef TAXI_SERVICE_HPP
#define TAXI_SERVICE_HPP

#include "task_service.hpp"
#include "../tasks/taxi_task.hpp"
#include "../systems/service_system.hpp"

class TaxiService : public TaskService
{
    public:
        TaxiService(const std::string& id, const Guest&, const jed_utils::datetime&);
        void add_to_systems(ServiceSystem&) override;
        const std::string& get_description() const noexcept override;
        std::vector<const Task*> get_tasks() const override;
        const TaxiTask& get_taxitask() const;
        Amount get_default_price() const noexcept override;
    private:
        static const std::string description;
        jed_utils::datetime time;
        std::string taxitask_id;
};

#endif
