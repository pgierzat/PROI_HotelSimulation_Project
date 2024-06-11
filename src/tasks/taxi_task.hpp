#ifndef TAXI_TASK_HPP
#define TAXI_TASK_HPP

#include "small_task.hpp"
#include "../auxiliary/own_system_observer.hpp"
#include "../rooms/hpp/room.hpp"
#include "../types/datetime.h"
#include "../types/guest.hpp"
#include "../workers/receptionist.hpp"

class TaxiTask : public SmallTask<Receptionist>, protected OwnSystemObserver<Guest>
{
        using GuestObs = OwnSystemObserver<Guest>;
    public:
        TaxiTask(const std::string& id, const Guest&, const jed_utils::datetime&);
        const Guest& get_guest() const noexcept;
        const jed_utils::datetime& get_time() const noexcept;
        void set_guest(const Guest&) noexcept;
        void set_time(const jed_utils::datetime&) noexcept;
        const std::string& get_description() const noexcept override;
    protected:   
        static const std::string description;
        jed_utils::datetime time;
};

#endif
