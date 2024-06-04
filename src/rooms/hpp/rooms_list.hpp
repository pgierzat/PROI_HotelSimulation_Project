#ifndef ROOMS_LIST_HPP
#define ROOMS_LIST_HPP

#include "room.hpp"
#include <list>
#include <optional>
#include <memory>
#include <vector>

class RoomsList
{
    private:
        std::list<std::unique_ptr<Room>> rooms;
    public:
        void add_room(unsigned number);
        void add_one_room(unsigned number);
        void add_two_room(unsigned number);
        void add_three_room(unsigned number);
        void add_four_room(unsigned number);
        void add_two_apartment(unsigned number);
        void add_four_apartment(unsigned number);

        Amount calculate_total_price() const noexcept;

        std::optional<const Room*> find_by_number(unsigned number) const noexcept;
        const Room& get_by_number(unsigned number) const;
        const std::list<std::unique_ptr<Room>>& getRooms() const noexcept;
        void display() const;
        bool room_exists(unsigned number) const;

};

#endif