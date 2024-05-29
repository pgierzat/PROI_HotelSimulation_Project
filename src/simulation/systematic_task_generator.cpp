#include "systematic_task_generator.hpp"
#include "../utilities/errors.hpp"
#include "../tasks/room_cleaning_task.hpp"
#include "../workers/maid.hpp"

SystematicTaskGenerator::SystematicTaskGenerator(TaskSystem& t_system,
    const RoomsList& rooms_list, const jed_utils::datetime& time) :
        t_system{&t_system}, rooms_list{&rooms_list}, time{time}
{
    auto maid = Maid{"foo", "42", Pay{PaycheckMethod::Wage, Amount{0, 0}}};
    time_of_gen = maid.get_shift_start(Shift::I);
    set_time_next();
    auto timecpy = time;
    timecpy.trunkate();
    if (time < timecpy + time_of_gen)
        time_next.add_days(-1);
}

void SystematicTaskGenerator::set_time(const jed_utils::datetime& time)
{
    auto prev_time = this -> time;
    if (time < prev_time)
        throw TurnBackTimeError("Tried to turn SystematicTaskGenerator's time back.", time);
    if (time_next <= time)
    {
        generate_room_cleaning_tasks();
        set_time_next();
    }
    this -> time = time;
}

void SystematicTaskGenerator::generate_room_cleaning_tasks()
{
    for (const auto& room : rooms_list -> getRooms())
        t_system -> add_task_id(RoomCleaningTask{"foo", *room});
}

void SystematicTaskGenerator::set_time_next() noexcept
{
    time_next = time;
    time_next.trunkate().add_days(1);
    time_next += time_of_gen;
}
