#include "../hpp/three_room.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"

ThreeRoom::ThreeRoom(const std::string& number) :
Room(number, capacity=3)
{}

Amount ThreeRoom::calculatePrice() const
{
    return base_price * 2.5;
}

RoomType ThreeRoom::get_type() const noexcept { return type; }
