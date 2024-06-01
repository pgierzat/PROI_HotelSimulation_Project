#include <string>
#include <memory>
#include "worker.hpp"
#include "worker_maps.hpp"
#include "../utilities/errors.hpp"
#include "../paycheck_calculators/salary_calculator.hpp"
#include "../paycheck_calculators/wage_calculator.hpp"


Worker::Worker(std::string id, std::string name, const Pay& pay) :
    id{id}, name{name}, pay{pay}
{
    calculator = create_calculator(this, pay.get_method());
}

Worker::Worker(const Worker& copied) :
    id{copied.id},name{copied.name}, pay{copied.pay}
{
    calculator = create_calculator(this, pay.get_method());
}

Worker::Worker(Worker&& moved) : id{moved.id}, name{moved.name}, pay{moved.pay},
    calculator{std::move(moved.calculator)} {}

Worker& Worker::operator=(const Worker& copied)
{
    name = copied.name;
    id = copied.id;
    pay = copied.pay;
    calculator = create_calculator(this, pay.get_method());
    return *this;
}

Worker& Worker::operator=(Worker&& moved)
{
    name = moved.name;
    id = moved.id;
    pay = moved.pay;
    calculator = std::move(moved.calculator);
    return *this;
}

std::string Worker::get_name() const noexcept { return name; }
std::string Worker::get_id() const noexcept { return id; }
Pay Worker::get_pay() const noexcept { return pay; }

Amount Worker::calculate_base_paycheck(unsigned hours_worked) const noexcept
{
    return calculator -> calculate_paycheck(hours_worked);
}

void Worker::set_name(const std::string& name) { this -> name = name; }
void Worker::set_id(const std::string& id) { this -> id = id; };

void Worker::set_pay(const Pay& pay)
{
    this -> pay = pay;
    calculator = create_calculator(this, pay.get_method());
}

bool Worker::operator==(const Worker& other) const
{
    return name == other.name &&
        id == other.id &&
        pay == other.pay;
}

std::unique_ptr<PaycheckCalculator> Worker::create_calculator(Worker* that, PaycheckMethod method)
{
    std::unique_ptr<PaycheckCalculator> calculator = nullptr;
    switch (method)
    {
        case PaycheckMethod::Salary:
            calculator = std::make_unique<SalaryCalculator>(*that);
            break;
        case PaycheckMethod::Wage:
            calculator = std::make_unique<WageCalculator>(*that);
            break;
        default:
            throw std::invalid_argument("This PaycheckMethod isn't supported.");
    }
    return calculator;
}

std::ostream& operator<<(std::ostream& os, const Worker& worker)
{
    return os << worker.get_id() << ' ' << worker.get_name() << ' ' << Worker::wtype_to_str(worker.get_type());
}

const Shift Worker::str_to_shift(const std::string& str)
{
    try {
        return str_to_shift_map.at(str);
    } catch (const std::out_of_range& e) {
        throw InvalidShiftString{"Cannot convert that string to Shift.", str};
    }
}

const std::string& Worker::shift_to_str(Shift shift) { return shift_to_str_map.at(shift); }

const WorkerType Worker::str_to_wtype(const std::string& str)
{
    try {
        return str_to_wtype_map.at(str);
    } catch (const std::out_of_range& e) {
        throw InvalidWorkerTypeString{"Cannot convert that string to WorkerType.", str};
    }
}

const std::string& Worker::wtype_to_str(WorkerType wtype) { return wtype_to_str_map.at(wtype); }
