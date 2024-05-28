#include "../hpp/room.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"
#include <iostream>


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


void Room::display(std::ostream& os) const {
    os << "Room number: " << getNumber() << "\n";
    os << "Capacity: " << getCapacity() << "\n";
    os << "Base price: " << calculatePrice() << "\n";
}


std::ostream& operator<<(std::ostream& os, const Room& room) {
    room.display(os);
    return os;
}