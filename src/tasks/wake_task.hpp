#ifndef WAKE_TASK_HPP
#define WAKE_TASK_HPP

#include "small_task.hpp"
#include "../auxiliary/own_system_observer.hpp"
#include "../auxiliary/pseudo_own_system_observer.hpp"
#include "../rooms/hpp/room.hpp"
#include "../types/datetime.h"
#include "../workers/maid.hpp"

class WakeTask :
    public SmallTask<Maid>,
    protected OwnSystemObserver<Room>,
    protected PseudoOwnSystemObserver<Guest>
{
        using RoomObs = OwnSystemObserver<Room>;
    public:
        WakeTask(const std::string& id, const Room&, const jed_utils::datetime&);
        const Room& get_room() const noexcept;
        const jed_utils::datetime& get_time() const noexcept;
        void set_room(const Room&) noexcept;
        void set_time(const jed_utils::datetime&) noexcept;
        const std::string& get_description() const noexcept override;
    protected:   
        static const std::string description;
        jed_utils::datetime time;
};

#endif
