#ifndef ROOM_CLEANING_TASK_HPP
#define ROOM_CLEANING_TASK_HPP

#include <vector>
#include "big_task.hpp"
#include "../auxiliary/own_system_observer.hpp"
#include "../workers/maid.hpp"
#include "../rooms/hpp/room.hpp"


class RoomCleaningTask : public BigTask<Maid>, protected OwnSystemObserver<Room>
{
        using RoomObs = OwnSystemObserver<Room>;
    public:
        RoomCleaningTask(const std::string& id, const Room&);
        const Room& get_room() const noexcept;
        void set_room(const Room&) noexcept;
};


#endif
