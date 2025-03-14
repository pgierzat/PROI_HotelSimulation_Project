#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "../systems/task_system.hpp"
#include "../systems/worker_system.hpp"
#include "../systems/clock.hpp"
#include "../systems/timetable_system.hpp"
#include "../systems/hotel_system.hpp"
#include "../systems/paycheck_system.hpp"
#include "../types/datetime.h"
#include "stay_generator.hpp"
#include "room_cleaning_task_generator.hpp"
#include "timetable_generator.hpp"

class Simulator {
    HotelSystem& hotel_system;
    StayGenerator stay_generator;
    RoomCleaningTaskGenerator room_cleaning_task_generator;
    TimetableGenerator timetable_generator;
public:
    Simulator(HotelSystem&);
    void simulate();
};


#endif
