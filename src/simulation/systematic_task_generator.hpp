#ifndef SYSTEMATIC_TASK_GENERATOR_HPP
#define SYSTEMATIC_TASK_GENERATOR_HPP

#include "../systems/task_system.hpp"
#include "../types/datetime.h"
#include "../types/timespan.h"


class SystematicTaskGenerator
{
    public:
        SystematicTaskGenerator(TaskSystem&, const RoomsList&);
        void set_time(const jed_utils::datetime&);
        void generate_room_cleaning_tasks();
    private:
        TaskSystem* t_system;
        const RoomsList* rooms_list;
        jed_utils::datetime time{1970, 1, 1};
};

#endif
