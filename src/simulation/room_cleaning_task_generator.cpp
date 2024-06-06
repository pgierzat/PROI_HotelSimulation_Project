#include "room_cleaning_task_generator.hpp"
#include "../utilities/errors.hpp"
#include "../tasks/room_cleaning_task.hpp"
#include "../systems/hotel_system.hpp"

RoomCleaningTaskGenerator::RoomCleaningTaskGenerator(HotelSystem& h_system) :
    SystematicTaskGenerator{h_system.get_time(), h_system.get_t_system()},
    rooms_list{&h_system.get_crooms_list()}
{
    initiate_time_next();
}

void RoomCleaningTaskGenerator::generate()
{
    for (const auto& room : rooms_list -> getRooms())
        t_system -> add_task_id(RoomCleaningTask{"foo", *room});
}

void RoomCleaningTaskGenerator::initiate_time_next()
{
    time_next = time;
    time_next.trunkate();
    time_next += get_time_of_gen();
    if (time >= time_next)
        time_next.add_days(1);
}

jed_utils::timespan RoomCleaningTaskGenerator::get_time_of_gen() const noexcept {
    return Maid{}.get_shift_start(Shift::I);
}
