#ifndef PREPARE_DISH_TASK_HPP
#define PREPARE_DISH_TASK_HPP

#include <vector>
#include "big_task.hpp"
#include "../workers/maid.hpp"
#include "../rooms/hpp/room.hpp"


class RoomCleaningTask : public BigTask<Maid>
{
    public:
        RoomCleaningTask(const std::string& id, const Room&);
        const Room& get_room() const noexcept;
    protected:
        const Room& room;
};


#endif
