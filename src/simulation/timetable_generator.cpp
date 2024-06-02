#include "timetable_generator.hpp"


TimetableGenerator::TimetableGenerator(const jed_utils::datetime& time, TimetableSystem& tt_system,
    const WorkerSystem& w_system) : Generator{time}, tt_system{&tt_system}, w_system{&w_system}
{
    initiate_time_next();
}

void TimetableGenerator::generate()
{
    auto next_monday = time_next;
    next_monday.add_days(8);
    auto cook_entries = generate_empty_entries<Cook>(next_monday);
    assign_entries<Cook>(cook_entries);
    auto maid_entries = generate_empty_entries<Maid>(next_monday);
    assign_entries<Maid>(maid_entries);
    auto receptionist_entries = generate_empty_entries<Receptionist>(next_monday);
    assign_entries<Receptionist>(receptionist_entries);
    auto waiter_entries = generate_empty_entries<Waiter>(next_monday);
    assign_entries<Waiter>(waiter_entries);
}

void TimetableGenerator::initiate_time_next()
{
    auto weekday = time.get_weekday();
    auto weakday_int = static_cast<unsigned>(weekday);    // sunday = 0
    time_next = time;
    time_next.trunkate();
    time_next.add_days(-weakday_int);
    time_next += get_time_of_gen();
    if (time >= time_next)
        time_next.add_days(7);
}

void TimetableGenerator::set_time_next() noexcept
{
    time_next.add_days(7);
}
