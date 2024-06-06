#include "../hpp/rooms_list.hpp"
#include "../hpp/room.hpp"
#include "../hpp/one_room.hpp"
#include "../hpp/two_room.hpp"
#include "../hpp/three_room.hpp"
#include "../hpp/four_room.hpp"
#include "../hpp/two_appartment.hpp"
#include "../hpp/four_appartment.hpp"
#include "../../utilities/errors.hpp"
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>


RoomsList::RoomsList(std::list<std::unique_ptr<Room>> rooms) : rooms(std::move(rooms)) {}

Amount RoomsList::calculate_total_price() const noexcept
{
    return std::accumulate(rooms.begin(), rooms.end(), Amount{0, 0}, [](Amount sum, const std::unique_ptr<Room>& room) { return sum + room->calculatePrice(); });
}

std::optional<const Room*> RoomsList::find_by_id(const std::string& id) const noexcept
{
    auto found_room = std::find_if(rooms.begin(), rooms.end(),
        [=](const std::unique_ptr<Room>& room) { return room->get_id() == id; });
    if (found_room == rooms.end())
        return std::nullopt;
    return &**found_room;
}

const Room& RoomsList::get_by_id(const std::string& id) const
{
    auto found_room = std::find_if(rooms.begin(), rooms.end(),
        [=](const std::unique_ptr<Room>& room) { return room->get_id() == id; });
    if (found_room == rooms.end())
        throw RoomNotInSystemError("get_by_id failed.", id);
    return **found_room;
}

const std::list<std::unique_ptr<Room>>& RoomsList::getRooms() const noexcept
{
    return rooms;
}


void RoomsList::display() const {
    for (const auto& room : rooms) {
        std::cout << *room << "\n";
    }
}

bool RoomsList::room_exists(const std::string& id) const
{
    return std::find_if(rooms.begin(), rooms.end(),
        [&](const auto& room) { return room -> get_id() == id; }) != rooms.end();
}

