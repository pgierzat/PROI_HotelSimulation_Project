#include "../hpp/four_appartment.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"


FourAppartment::FourAppartment(const std::string& number) :
Room(number, capacity=4)
{}

Amount FourAppartment::calculatePrice() const
{
    return base_price * 5;
}

unsigned FourAppartment::calculatePersonel() const
{
    return 3;
}

RoomType FourAppartment::get_type() const noexcept { return type; }
