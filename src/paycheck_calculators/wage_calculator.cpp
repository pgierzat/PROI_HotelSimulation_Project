#include "wage_calculator.hpp"
#include "../workers/worker.hpp"

WageCalculator::WageCalculator(const Worker& worker) : PaycheckCalculator{worker} {}

Amount WageCalculator::calculate_paycheck() const noexcept
{
    return worker -> get_wage() *  worker -> get_hours_worked();
}
