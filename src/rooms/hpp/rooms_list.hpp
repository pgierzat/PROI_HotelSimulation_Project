#ifndef ROOMS_LIST_HPP
#define ROOMS_LIST_HPP

#include "room.hpp"
#include "../../auxiliary/other_system_observer.hpp"
#include "../../auxiliary/other_system_publisher.hpp"
#include "../../utilities/concepts.hpp"
#include <list>
#include <optional>
#include <memory>
#include <vector>


class RoomsList : public OtherSystemPublisher<Room>
{
    private:
        std::list<std::unique_ptr<Room>> rooms;
    public:
        void add_room(unsigned number);
        void add_one_room(unsigned number);
        void add_two_room(unsigned number);
        void add_three_room(unsigned number);
        void add_four_room(unsigned number);
        void add_two_appartment(unsigned number);
        void add_four_appartment(unsigned number);
        RoomsList() = default;
        RoomsList(std::list<std::unique_ptr<Room>> rooms);

        Amount calculate_total_price() const noexcept;
        unsigned calculate_total_rooms() const noexcept;
        std::optional<const Room*> find_by_id(const std::string& number) const noexcept;
        const Room& get_by_id(const std::string& number) const;
        const std::list<std::unique_ptr<Room>>& getRooms() const noexcept;
        void display() const;
        bool room_exists(const std::string& number) const;

};


template<SupportedRoom T>
void RoomsList::add_room(const T& room)
{
    if (room_exists(room.get_id()))
        throw std::invalid_argument("Tried to add a Room with duplicate id to RoomsList.");
    auto to_add = std::make_unique<T>(room);
    auto p = rooms.begin();
    rooms.push_back(std::move(to_add));
    if (rooms.begin() != p)
        publish_realloc();
}

#endif