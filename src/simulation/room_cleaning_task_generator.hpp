#ifndef ROOM_CLEANING_TASK_GENERATOR
#define ROOM_CLEANING_TASK_GENERATOR

#include "systematic_task_generator.hpp"
#include "../workers/maid.hpp"

class RoomCleaningTaskGenerator : public SystematicTaskGenerator
{
    public:
        RoomCleaningTaskGenerator(TaskSystem&, const RoomsList&, const jed_utils::datetime&);
    private:
        void initiate_time_next();
        void generate() override;
        jed_utils::timespan get_time_of_gen() const noexcept override;
        const RoomsList* rooms_list;
};


#endif
