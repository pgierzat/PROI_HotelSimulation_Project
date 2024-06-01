#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>
#include <map>
#include <string>
#include "../../types/amount.hpp"

enum class RoomType {
    Room,
    OneRoom,
    TwoRoom,
    ThreeRoom,
    FourRoom,
    TwoAppartment,
    FourAppartment,
};

class Room {

    protected:
        unsigned number;
        unsigned capacity;
        static const Amount base_price;
    public:
        Room(unsigned number, unsigned capacity);
        virtual ~Room() = default;
        virtual unsigned calculatePersonel() const;
        virtual Amount calculatePrice() const;
        virtual void display(std::ostream& os) const;
        unsigned getNumber() const;
        unsigned getCapacity() const;
        virtual RoomType get_type() const noexcept;
        virtual bool operator==(const Room&) const = default;
        friend std::ostream& operator<<(std::ostream& os, const Room& room);
        static const std::string& rtype_to_str(RoomType);
        static RoomType str_to_rtype(const std::string&);
        static const RoomType type = RoomType::Room;
    private:
        static const std::map<std::string, RoomType> str_to_rtype_map;
        static const std::map<RoomType, std::string> rtype_to_str_map;
};


#endif