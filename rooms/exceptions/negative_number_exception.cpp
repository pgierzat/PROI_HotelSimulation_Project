#include "negative_number_exception.hpp"

NegativeNumberException::NegativeNumberException(unsigned wrong_number) :
std::invalid_argument("Number cannot be negative"), number(wrong_number) {}

unsigned NegativeNumberException::get_number() const
{
    return number;
}