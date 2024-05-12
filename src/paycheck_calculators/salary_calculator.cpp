#include "salary_calculator.hpp"
#include "../workers/worker.hpp"

SalaryCalculator::SalaryCalculator(const Worker& worker) :
    PaycheckCalculator{worker} {}

Amount SalaryCalculator::calculate_paycheck(unsigned hours_worked) const noexcept
{
    return (worker -> get_pay()).get_salary();
}
