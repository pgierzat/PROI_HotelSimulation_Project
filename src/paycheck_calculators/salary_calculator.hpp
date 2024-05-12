#include "paycheck_calculator.hpp"

#ifndef SALARY_CALCULATOR
#define SALARY_CALCULATOR

class SalaryCalculator : public PaycheckCalculator
{
    public:
        SalaryCalculator(const Worker&);
        Amount calculate_paycheck(unsigned hours_worked) const noexcept override;
};

#endif