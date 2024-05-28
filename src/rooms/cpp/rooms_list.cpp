#include "../hpp/rooms_list.hpp"
#include "../hpp/room.hpp"
#include "../hpp/one_room.hpp"
#include "../hpp/two_room.hpp"
#include "../hpp/three_room.hpp"
#include "../hpp/four_room.hpp"
#include "../hpp/two_apartment.hpp"
#include "../hpp/four_apartment.hpp"
#include "../../utilities/errors.hpp"
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

void RoomsList::add_room(unsigned number)
{
    if (room_exists(number)) {
        std::cout << "Room with number " << number << " already exists.\n";
        return;
    }
    std::unique_ptr<Room> added_room = std::make_unique<Room>(number, 1);
    rooms.push_back(std::move(added_room));
}

void RoomsList::add_one_room(unsigned number)
{
    if (room_exists(number)) {
        std::cout << "Room with number " << number << " already exists.\n";
        return;
    }
    std::unique_ptr<OneRoom> added_one_room = std::make_unique<OneRoom>(number);
    rooms.push_back(std::move(added_one_room));
}

void RoomsList::add_two_room(unsigned number)
{
    if (room_exists(number)) {
        std::cout << "Room with number " << number << " already exists.\n";
        return;
    }
    std::unique_ptr<TwoRoom> added_two_room = std::make_unique<TwoRoom>(number);
    rooms.push_back(std::move(added_two_room));
}

void RoomsList::add_three_room(unsigned number)
{
    if (room_exists(number)) {
        std::cout << "Room with number " << number << " already exists.\n";
        return;
    }
    std::unique_ptr<ThreeRoom> added_three_room = std::make_unique<ThreeRoom>(number);
    rooms.push_back(std::move(added_three_room));
}

void RoomsList::add_four_room(unsigned number)
{
    if (room_exists(number)) {
        std::cout << "Room with number " << number << " already exists.\n";
        return;
    }
    std::unique_ptr<FourRoom> added_four_room = std::make_unique<FourRoom>(number);
    rooms.push_back(std::move(added_four_room));
}

void RoomsList::add_two_apartment(unsigned number)
{
    if (room_exists(number)) {
        std::cout << "Room with number " << number << " already exists.\n";
        return;
    }
    std::unique_ptr<TwoApartment> added_two_apartment = std::make_unique<TwoApartment>(number);
    rooms.push_back(std::move(added_two_apartment));
}

void RoomsList::add_four_apartment(unsigned number)
{
    if (room_exists(number)) {
        std::cout << "Room with number " << number << " already exists.\n";
        return;
    }
    std::unique_ptr<FourApartment> added_four_apartment = std::make_unique<FourApartment>(number);
    rooms.push_back(std::move(added_four_apartment));
}


Amount RoomsList::calculate_total_price() const noexcept
{
    return std::accumulate(rooms.begin(), rooms.end(), Amount{0, 0}, [](Amount sum, const std::unique_ptr<Room>& room) { return sum + room->calculatePrice(); });
}

std::optional<const Room*> RoomsList::find_by_number(unsigned number) const noexcept
{
    auto found_room = std::find_if(rooms.begin(), rooms.end(),
        [=](const std::unique_ptr<Room>& room) { return room->getNumber() == number; });
    if (found_room == rooms.end())
        return std::nullopt;
    return &**found_room;
}

const Room& RoomsList::get_by_number(unsigned number) const
{
    auto found_room = std::find_if(rooms.begin(), rooms.end(),
        [=](const std::unique_ptr<Room>& room) { return room->getNumber() == number; });
    if (found_room == rooms.end())
        throw RoomNotInSystemError("get_by_number failed.", number);
    return **found_room;
}

std::list<std::unique_ptr<Room>>& RoomsList::getRooms() noexcept
{
    return rooms;
}


void RoomsList::display() const {
    for (const auto& room : rooms) {
        std::cout << *room << "\n";
    }
}

bool RoomsList::room_exists(unsigned number) const
{
    return std::find_if(rooms.begin(), rooms.end(), [number](const std::unique_ptr<Room>& room) { return room->getNumber() == number; }) != rooms.end();
}

