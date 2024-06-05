#include "stay_generator.hpp"
#include "../utilities/errors.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "../systems/stay_system.hpp"
#include "../types/stay.hpp"
#include "../types/guest.hpp"
#include "../auxiliary/id_generator.hpp"
#include "../rooms/hpp/one_room.hpp"
#include "../rooms/hpp/two_room.hpp"
#include "../rooms/hpp/three_room.hpp"
#include "../rooms/hpp/four_room.hpp"
#include <random>
#include <algorithm>
#include <vector>

StayGenerator::StayGenerator(StaySystem& s_system, const RoomsList& rooms_list,
    const jed_utils::datetime& time) : Generator{time}, s_system{&s_system},
    rooms_list{&rooms_list}
{
    initiate_time_next();
}

void StayGenerator::generate()
{
    IDGenerator IDGenerator;
    std::srand(std::time(0));
    int guests = std::rand() % 4 + 1;
    int days = std::rand() % 7 + 1;
    std::vector<Guest> guestslist;
    for (int guests; guests = 0 ; guests--){
        Guest guest = Guest(IDGenerator.generate_id(), "guest");
        guestslist.push_back(guest);
    }
    switch (guests)
    {
    case 1:
        std::vector<Room> rooms = rooms_list -> getRooms();
        OneRoom free_room = find_if(rooms.begin(), rooms.end(), [](OneRoom room) {return s_system -> check_room(room);});
        if(free_room == rooms.end())
            break;
        Guest main_guest = guestslist[0];
        jed_utils::datetime end_time = time.add_days(days);
        Stay stay = Stay(IDGenerator.generate_id(), free_room, main_guest, time, end_time);
        s_system -> add_stay(stay);
    case 2:
        std::vector<Room> rooms = rooms_list -> getRooms();
        Guest main_guest = guestslist[0];
        TwoRoom free_room = find_if(rooms.begin(), rooms.end(), rooms.end(), [](TwoRoom room) {return s_system -> check_room(room);});
        if(free_room == rooms.end())
            break;
        jed_utils::datetime end_time = time.add_days(days);
        Stay stay = Stay(IDGenerator.generate_id(), free_room, main_guest, time, end_time);
        s_system -> add_stay(stay);
    case 3:
        std::vector<Room> rooms = rooms_list -> getRooms();
        Guest main_guest = guestslist[0];
        ThreeRoom free_room = find_if(rooms.begin(), rooms.end(), [](ThreeRoom room) {return s_system -> check_room(room);});
        if(free_room == rooms.end())
            break;
        jed_utils::datetime end_time = time.add_days(days);
        Stay stay = Stay(IDGenerator.generate_id(), free_room, main_guest, time, end_time);
        s_system -> add_stay(stay);
    case 4:
        std::vector<Room> rooms = rooms_list -> getRooms();
        Guest main_guest = guestslist[0];
        FourRoom free_room = find_if(rooms.begin(), rooms.end(), [](FourRoom room) {return s_system -> check_room(room);});
        if(free_room == rooms.end())
            break;
        jed_utils::datetime end_time = time.add_days(days);
        Stay stay = Stay(IDGenerator.generate_id(), free_room, main_guest, time, end_time);
        s_system -> add_stay(stay);
    default:
        break;
    }
}

void StayGenerator::initiate_time_next()
{
    std::srand(std::time(0));
    int hours = std::rand() % 4 + 1;
    time_next = time;
    time_next.trunkate();
    if(time >= time_next)
        time_next.add_hours(hours);
}