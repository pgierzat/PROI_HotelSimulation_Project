#include "../hpp/two_room.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"

TwoRoom::TwoRoom(unsigned number) :
Room(number, capacity=2)
{}

Amount TwoRoom::calculatePrice() const
{
    return base_price * 1.8;
}
