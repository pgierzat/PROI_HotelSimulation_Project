#include "../hpp/two_room.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"

TwoRoom::TwoRoom(const std::string& number) :
Room(number, capacity=2)
{}

Amount TwoRoom::calculatePrice() const
{
    return base_price * 1.8;
}

RoomType TwoRoom::get_type() const noexcept { return type; }
