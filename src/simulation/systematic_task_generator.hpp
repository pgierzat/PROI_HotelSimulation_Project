#ifndef SYSTEMATIC_TASK_GENERATOR_HPP
#define SYSTEMATIC_TASK_GENERATOR_HPP

#include "../systems/task_system.hpp"
#include "../types/datetime.h"
#include "../types/timespan.h"
#include "../workers/maid.hpp"


class SystematicTaskGenerator
{
    public:
        SystematicTaskGenerator(TaskSystem&, const RoomsList&, const jed_utils::datetime&);
        void set_time(const jed_utils::datetime&);
    private:
        void generate_room_cleaning_tasks();
        void set_time_next() noexcept;
        TaskSystem* t_system;
        const RoomsList* rooms_list;
        jed_utils::datetime time;
        jed_utils::datetime time_next;
        jed_utils::timespan time_of_gen{0};
};

#endif
