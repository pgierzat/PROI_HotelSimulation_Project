#include "../hpp/one_room.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"

OneRoom::OneRoom(unsigned number) :
Room(number, capacity=1)
{}

Amount OneRoom::calculatePrice() const
{
    return base_price;
}
