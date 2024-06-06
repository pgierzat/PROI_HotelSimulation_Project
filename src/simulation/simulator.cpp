#include "stay_generator.hpp"
#include "room_cleaning_task_generator.hpp"
#include "timetable_generator.hpp"
#include "generator.hpp"
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

Simulator::Simulator(HotelSystem& hotel_system, WorkerSystem& worker_system, RoomsList& rooms_list) :
    hotel_system(hotel_system),
    worker_system(worker_system),
    rooms_list(rooms_list),
    stay_generator(hotel_system.get_s_system(), rooms_list, hotel_system.get_ck().get_time()),
    room_cleaning_task_generator(hotel_system.get_t_system(), rooms_list, hotel_system.get_ck().get_time()),
    timetable_generator(hotel_system.get_ck().get_time(), hotel_system.get_tt_system(), worker_system)
{}

void Simulator::simulate()
{
    // Simulation loop
    while (true)
    {
        hotel_set_time(hotel_system.get_ck().get_time());
    }
}

void Simulator::hotel_set_time(const jed_utils::datetime& time)
{
    stay_generator.set_time(time);
    room_cleaning_task_generator.set_time(time);
    timetable_generator.set_time(time);
}


