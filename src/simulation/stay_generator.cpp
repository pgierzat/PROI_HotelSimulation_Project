#include "stay_generator.hpp"
#include "../systems/hotel_system.hpp"
#include "../types/guest.hpp"
#include "../auxiliary/id_generator.hpp"
#include "../rooms/hpp/one_room.hpp"
#include "../rooms/hpp/two_room.hpp"
#include "../rooms/hpp/three_room.hpp"
#include "../rooms/hpp/four_room.hpp"
#include <random>
#include <algorithm>
#include <vector>

StayGenerator::StayGenerator(HotelSystem& h_system) : Generator{time},
    rooms_list{&h_system.get_crooms_list()}, s_system{&h_system.get_s_system()}
{
    initiate_time_next();
}

void StayGenerator::generate()
{
    IDGenerator IDGenerator;
    std::srand(std::time(0));
    int guests = std::rand() % 4 + 1;
    int days = std::rand() % 7 + 1;
    std::vector<Guest> guestslist{};
    for (; guests != 0 ; guests--){
        Guest guest = Guest(IDGenerator.generate_id(), "guest");
        guestslist.push_back(guest);
    }
    switch (guests)
    {
    case 1:
    {
        const std::list<std::unique_ptr<Room>>& rooms = rooms_list -> getRooms();
        Guest main_guest = guestslist[0];
        auto it = find_if(rooms.begin(), rooms.end(), [this](const std::unique_ptr<Room>& room) {return s_system -> check_room(*room);});
        if(it == rooms.end())
            break;
        OneRoom* free_room = dynamic_cast<OneRoom*>(it->get());
        if(!free_room)
            break;
        jed_utils::datetime end_time = time + jed_utils::timespan(days);
        Stay stay = Stay(IDGenerator.generate_id(), *free_room, main_guest, time, end_time);
        s_system -> add_stay(stay);
        break;
    }
    case 2:
    {
        const std::list<std::unique_ptr<Room>>& rooms = rooms_list -> getRooms();
        Guest main_guest = guestslist[0];
        auto it = find_if(rooms.begin(), rooms.end(), [this](const std::unique_ptr<Room>& room) {return s_system -> check_room(*room);});
        if(it == rooms.end())
            break;
        TwoRoom* free_room = dynamic_cast<TwoRoom*>(it->get());
        if(!free_room)
            break;
        jed_utils::datetime end_time = time + jed_utils::timespan(days);
        Stay stay = Stay(IDGenerator.generate_id(), *free_room, main_guest, time, end_time);
        s_system -> add_stay(stay);
        break;
    }
    case 3:
    {
        const std::list<std::unique_ptr<Room>>& rooms = rooms_list -> getRooms();
        Guest main_guest = guestslist[0];
        auto it = find_if(rooms.begin(), rooms.end(), [this](const std::unique_ptr<Room>& room) {return s_system -> check_room(*room);});
        if(it == rooms.end())
            break;
        ThreeRoom* free_room = dynamic_cast<ThreeRoom*>(it->get());
        if(!free_room)
            break;
        jed_utils::datetime end_time = time + jed_utils::timespan(days);
        Stay stay = Stay(IDGenerator.generate_id(), *free_room, main_guest, time, end_time);
        s_system -> add_stay(stay);
        break;
    }
    case 4:
        {
        const std::list<std::unique_ptr<Room>>& rooms = rooms_list -> getRooms();
        Guest main_guest = guestslist[0];
        auto it = find_if(rooms.begin(), rooms.end(), [this](const std::unique_ptr<Room>& room) {return s_system -> check_room(*room);});
        if(it == rooms.end())
            break;
        FourRoom* free_room = dynamic_cast<FourRoom*>(it->get());
        if(!free_room)
        break;
        jed_utils::datetime end_time = time + jed_utils::timespan(days);
        Stay stay = Stay(IDGenerator.generate_id(), *free_room, main_guest, time, end_time);
        s_system -> add_stay(stay);
        break;
        }
    default:
        break;
    }
}

void StayGenerator::set_time_next() noexcept
{
    std::srand(std::time(0));
    int hours = std::rand() % 4 + 1;
    time_next = time;
    time_next.add_hours(hours);
}

void StayGenerator::initiate_time_next()
{
    std::srand(std::time(0));
    int hours = std::rand() % 4 + 1;
    time_next = time;
    time_next.trunkate();
    time_next += get_time_of_gen();
    if (time >= time_next)
        time_next.add_hours(hours);
}