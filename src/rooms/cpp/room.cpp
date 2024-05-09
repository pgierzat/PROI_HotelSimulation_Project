#include "../hpp/room.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"
#include <iostream>

Room::Room(unsigned number, unsigned capacity) :
number(number), capacity(capacity), base_price(100)
{
    if(number <=0)
    {
        throw NegativeNumberException(number);
    }

    if(capacity <=0)
    {
        throw NegativeCapacityException(capacity);
    }
}

unsigned Room::calculatePrice() const
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


void Room::display(std::ostream& os) const {
    os << "Room number: " << getNumber() << "\n";
    os << "Capacity: " << getCapacity() << "\n";
    os << "Base price: " << calculatePrice() << "\n";
}


std::ostream& operator<<(std::ostream& os, const Room& room) {
    room.display(os);
    return os;
}