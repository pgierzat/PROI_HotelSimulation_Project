#ifndef ONE_ROOM_HPP
#define ONE_ROOM_HPP

#include "room.hpp"

class OneRoom : public Room
{
    public:
        OneRoom(const std::string& number);
        Amount calculatePrice() const override;
        virtual RoomType get_type() const noexcept override;
        static const RoomType type = RoomType::OneRoom;
};

#endif