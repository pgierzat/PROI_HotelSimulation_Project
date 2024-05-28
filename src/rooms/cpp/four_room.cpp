#include "../hpp/four_room.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"

FourRoom::FourRoom(unsigned number) :
Room(number, capacity=4)
{}

Amount FourRoom::calculatePrice() const
{
    return base_price * 3.5;
}