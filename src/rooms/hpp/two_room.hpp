#ifndef TWO_ROOM_HPP
#define TWO_ROOM_HPP

#include "room.hpp"

class TwoRoom : public Room
{
    public:
        TwoRoom(const std::string& number);
        Amount calculatePrice() const override;
        virtual RoomType get_type() const noexcept override;
        static const RoomType type = RoomType::TwoRoom;
};

#endif