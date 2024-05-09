#ifndef NEGATIVE_NUMBER_EXCEPTION_HPP
#define NEGATIVE_NUMBER_EXCEPTION_HPP

#include <stdexcept>

class NegativeNumberException : public std::invalid_argument
{
    private:
        unsigned number;
    public:
        NegativeNumberException(unsigned wrong_number);
        unsigned get_number() const;
};

#endif
