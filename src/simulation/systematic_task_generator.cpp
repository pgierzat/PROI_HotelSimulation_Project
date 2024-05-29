#include "systematic_task_generator.hpp"
#include "../utilities/errors.hpp"
#include "../tasks/room_cleaning_task.hpp"
#include "../workers/maid.hpp"

SystematicTaskGenerator::SystematicTaskGenerator(TaskSystem& t_system, const RoomsList& rooms_list) :
    t_system{&t_system}, rooms_list{&rooms_list}
{
    auto maid = Maid{"foo", "42", Pay{PaycheckMethod::Wage, Amount{0, 0}}};
    time_of_gen = maid.get_shift_start(Shift::I);
}

void SystematicTaskGenerator::set_time(const jed_utils::datetime& time)
{
    auto prev_time = this -> time;
    if (prev_time < time)
        throw TurnBackTimeError("Tried to turn SystematicTaskGenerator's time back.", time);
    if (time_next <= time)
    {
        generate_room_cleaning_tasks();
        time_next = time;
        time_next.trunkate().add_days(1);
        time_next += time_of_gen;
    }
}

void SystematicTaskGenerator::generate_room_cleaning_tasks()
{
    for (const auto& room : rooms_list -> getRooms())
        t_system -> add_task_id(RoomCleaningTask{"foo", *room});
}
