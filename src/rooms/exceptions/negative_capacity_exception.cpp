#include "negative_capacity_exception.hpp"

NegativeCapacityException::NegativeCapacityException(unsigned wrong_capacity) :
std::invalid_argument("Capacity cannot be negative"), capacity(wrong_capacity) {}

unsigned NegativeCapacityException::get_capacity() const
{
    return capacity;
}