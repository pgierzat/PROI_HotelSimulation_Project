#ifndef ROOM_CLEANING_TASK_GENERATOR
#define ROOM_CLEANING_TASK_GENERATOR

#include "daily_generator.hpp"
#include "../systems/task_system.hpp"
#include "../workers/maid.hpp"

class HotelSystem;

class RoomCleaningTaskGenerator : public DailyGenerator
{
    public:
        RoomCleaningTaskGenerator(HotelSystem&);
    private:
        void generate() override;
        TaskSystem* t_system = nullptr;
        const RoomsList* rooms_list = nullptr;
};


#endif
