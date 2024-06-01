#include "../hpp/room.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"
#include <iostream>


const std::map<std::string, RoomType> Room::str_to_rtype_map = {
    {"Room", RoomType::Room},
    {"OneRoom", RoomType::OneRoom},
    {"TwoRoom", RoomType::TwoRoom},
    {"ThreeRoom", RoomType::ThreeRoom},
    {"FourRoom", RoomType::FourRoom},
    {"TwoAppartment", RoomType::TwoAppartment},
    {"FourAppartment", RoomType::FourAppartment}
};

const std::map<RoomType, std::string> Room::rtype_to_str_map = {
    {RoomType::Room, "Room"},
    {RoomType::OneRoom, "OneRoom"},
    {RoomType::TwoRoom, "TwoRoom"},
    {RoomType::ThreeRoom, "ThreeRoom"},
    {RoomType::FourRoom, "FourRoom"},
    {RoomType::TwoAppartment, "TwoAppartment"},
    {RoomType::FourAppartment, "FourAppartment"}
};

const Amount Room::base_price{100, 0};

Room::Room(unsigned number, unsigned capacity) :
number(number), capacity(capacity)
{
    if(number <=0)
        throw NegativeNumberException(number);
    if(capacity <=0)
        throw NegativeCapacityException(capacity);
}

Amount Room::calculatePrice() const
{
    return base_price;
}

unsigned Room::calculatePersonel() const
{
    return 1;
}


unsigned Room::getNumber() const
{
    return number;
}

unsigned Room::getCapacity() const
{
    return capacity;
}

RoomType Room::get_type() const noexcept { return type; }

void Room::display(std::ostream& os) const {
    os << "Room number: " << getNumber() << "\n";
    os << "Capacity: " << getCapacity() << "\n";
    os << "Base price: " << calculatePrice() << "\n";
}


std::ostream& operator<<(std::ostream& os, const Room& room) {
    room.display(os);
    return os;
}

const std::string& Room::rtype_to_str(RoomType type) {
    return rtype_to_str_map.at(type);
}

RoomType Room::str_to_rtype(const std::string& type_str) {
    return str_to_rtype_map.at(type_str);
}
