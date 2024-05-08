#ifndef NEGATIVE_CAPACITY_EXCEPTION_HPP
#define NEGATIVE_CAPACITY_EXCEPTION_HPP

#include <stdexcept>

class NegativeCapacityException : public std::invalid_argument
{
    private:
        unsigned capacity;
    public:
        NegativeCapacityException(unsigned wrong_capacity);
        unsigned get_capacity() const;
};

#endif