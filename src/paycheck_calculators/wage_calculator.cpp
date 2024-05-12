#include "wage_calculator.hpp"
#include "../workers/worker.hpp"

WageCalculator::WageCalculator(const Worker& worker) : PaycheckCalculator{worker} {}

Amount WageCalculator::calculate_paycheck(unsigned hours_worked) const noexcept
{
    return (worker -> get_pay()).get_wage() *  hours_worked;
}
