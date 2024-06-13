#include "stay_generator.hpp"
#include "room_cleaning_task_generator.hpp"
#include "timetable_generator.hpp"
#include "simulator.hpp"
#include "../systems/task_system.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "../systems/stay_system.hpp"
#include "../systems/guest_system.hpp"
#include "../systems/task_system.hpp"
#include "../systems/worker_system.hpp"
#include "../systems/clock.hpp"
#include "../systems/timetable_system.hpp"
#include "../systems/hotel_system.hpp"
#include "../systems/paycheck_system.hpp"

Simulator::Simulator(HotelSystem& hotel_system) :
    hotel_system(hotel_system),
    stay_generator(hotel_system),
    room_cleaning_task_generator(hotel_system),
    timetable_generator(hotel_system) {}

void Simulator::simulate()
{
    auto &clock = hotel_system.get_ck();
    clock.set_unit_delta(jed_utils::timespan(0, 1, 0, 0));
    auto end = jed_utils::datetime{2024, 7, 1};
    while (clock.get_time() < end)
    {
        ++clock;
    }
}

