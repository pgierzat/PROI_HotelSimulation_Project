#ifndef TAXI_TASK_HPP
#define TAXI_TASK_HPP

#include "small_task.hpp"
#include "../rooms/hpp/room.hpp"
#include "../types/datetime.h"
#include "../types/guest.hpp"
#include "../workers/receptionist.hpp"

class TaxiTask : public SmallTask<Receptionist>
{
    public:
        TaxiTask(const std::string& id, const Guest&, const jed_utils::datetime&);
        const Guest& get_guest() const noexcept;
        const jed_utils::datetime& get_time() const noexcept;
    protected:
        const Guest& guest;
        jed_utils::datetime time;
};

#endif
