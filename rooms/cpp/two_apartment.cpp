#include "../hpp/two_apartment.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"

TwoApartment::TwoApartment(unsigned number) :
Room(number, capacity=2)
{}

unsigned TwoApartment::calculatePrice() const
{
    return base_price * 2.5;
}

unsigned TwoApartment::calculatePersonel() const
{
    return 2;
}