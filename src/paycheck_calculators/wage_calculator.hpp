#include "paycheck_calculator.hpp"

#ifndef WAGE_CALCULATOR
#define WAGE_CALCULATOR

class Worker;

class WageCalculator : public PaycheckCalculator
{
    public:
        WageCalculator(const Worker& worker);
        Amount calculate_paycheck() const noexcept override;
};

#endif
