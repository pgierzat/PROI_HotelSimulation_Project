#include "room_cleaning_task_generator.hpp"
#include "../utilities/errors.hpp"
#include "../tasks/room_cleaning_task.hpp"
#include "../systems/hotel_system.hpp"

RoomCleaningTaskGenerator::RoomCleaningTaskGenerator(HotelSystem& h_system) :
    DailyGenerator{h_system.get_ck(), Maid{}.get_shift_start(Shift::I)},
    t_system{&h_system.get_t_system()}, rooms_list{&h_system.get_crooms_list()}
{
    initiate_time_next();
}

void RoomCleaningTaskGenerator::generate()
{
    for (const auto& room : rooms_list -> getRooms())
        t_system -> add_task_id(RoomCleaningTask{"foo", *room});
}
