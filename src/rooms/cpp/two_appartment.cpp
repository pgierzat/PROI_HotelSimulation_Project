#include "../hpp/two_appartment.hpp"
#include "../exceptions/negative_number_exception.hpp"
#include "../exceptions/negative_capacity_exception.hpp"

TwoAppartment::TwoAppartment(unsigned number) :
Room(number, capacity=2)
{}

Amount TwoAppartment::calculatePrice() const
{
    return base_price * 2.5;
}

unsigned TwoAppartment::calculatePersonel() const
{
    return 2;
}

RoomType TwoAppartment::get_type() const noexcept { return type; }