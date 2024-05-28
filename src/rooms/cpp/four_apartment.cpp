#include "../hpp/four_apartment.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"


FourApartment::FourApartment(unsigned number) :
Room(number, capacity=4)
{}

Amount FourApartment::calculatePrice() const
{
    return base_price * 5;
}

unsigned FourApartment::calculatePersonel() const
{
    return 3;
}