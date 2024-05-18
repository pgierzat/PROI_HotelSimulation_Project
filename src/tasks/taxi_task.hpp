#ifndef ORDER_TAXI_TASK
#define ORDER_TAXI_TASK

#include "task.hpp"
#include "../rooms/hpp/room.hpp"
#include "../types/datetime.h"
#include "../types/guest.hpp"
#include "../workers/receptionist.hpp"

class TaxiTask : public Task
{
    public:
        TaxiTask(const std::string& id, const Guest&, const jed_utils::datetime&);
        const Guest& get_guest() const noexcept;
        const jed_utils::datetime& get_time() const noexcept;
        void assign(const Receptionist&);
        void unassign() noexcept override;
        const Receptionist& get_assignee() const override;
    protected:
        const Guest& guest;
        jed_utils::datetime time;
        const Receptionist* assignee = nullptr;
};

#endif
