#ifndef ROOM_CLEANING_TASK_GENERATOR
#define ROOM_CLEANING_TASK_GENERATOR

#include "systematic_task_generator.hpp"
#include "../workers/maid.hpp"

class HotelSystem;

class RoomCleaningTaskGenerator : public SystematicTaskGenerator
{
    public:
        RoomCleaningTaskGenerator(HotelSystem&);
    private:
        void generate() override;
        void initiate_time_next();
        jed_utils::timespan get_time_of_gen() const noexcept override;
        const RoomsList* rooms_list;
};


#endif
