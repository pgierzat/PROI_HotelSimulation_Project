#ifndef WAKE_SERVICE_HPP
#define WAKE_SERVICE_HPP

#include "task_service.hpp"
#include "../tasks/wake_task.hpp"


class WakeService : public TaskService, OwnSystemObserver<Room>
{
        using TasksObs = MultipleOwnSystemObserver<Task>;
        using RoomObs = OwnSystemObserver<Room>;
    public:
        WakeService(const std::string& id, const Guest&, const Room&, const jed_utils::datetime&);
        void add_to_systems(ServiceSystem&) override;
        const std::string& get_description() const noexcept override;
        const WakeTask& get_waketask() const;
        Amount get_default_price() const noexcept override;
    private:
        static const std::string description;
        jed_utils::datetime time;
        const Room* room = nullptr;
        const WakeTask* wake_task = nullptr;
};

#endif