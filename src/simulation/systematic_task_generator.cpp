#include "systematic_task_generator.hpp"
#include "../utilities/errors.hpp"
#include "../tasks/room_cleaning_task.hpp"
#include "../workers/maid.hpp"

SystematicTaskGenerator::SystematicTaskGenerator(TaskSystem& t_system, const RoomsList& rooms_list) :
    t_system{&t_system}, rooms_list{&rooms_list} {}

void SystematicTaskGenerator::set_time(const jed_utils::datetime& time)
{
    auto prev_time = this -> time;
    if (prev_time < time)
        throw TurnBackTimeError("Tried to turn SystematicTaskGenerator's time back.", time);
}

void SystematicTaskGenerator::generate_room_cleaning_tasks()
{
    for (const auto& room : rooms_list -> getRooms())
        t_system -> add_task_id(RoomCleaningTask{"foo", *room});
}
