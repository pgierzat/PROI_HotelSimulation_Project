#include <string>
#include <memory>
#include "worker.hpp"
#include "../paycheck_calculators/salary_calculator.hpp"
#include "../paycheck_calculators/wage_calculator.hpp"


Worker::Worker(std::string id, std::string name, const Pay& pay) :
    id{id}, name{name}, pay{pay}
{
    calculator = create_calculator(this, pay.get_method());
}

Worker::Worker(const Worker& copied) :
    name{copied.name}, id{copied.id}, pay{copied.pay}
{
    calculator = create_calculator(this, pay.get_method());
}

Worker::Worker(Worker&& moved) : name{moved.name}, id{moved.id}, pay{moved.pay},
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
    return os << worker.get_id() << ' ' << worker.get_name() << ' ' << worker.get_type();
}

std::ostream& operator<<(std::ostream& os, Shift shift)
{
    return os << shift_to_str.at(shift);
}

std::istream& operator>>(std::istream& is, Shift& shift)
{
    std::string shift_str;
    std::cin >> shift_str;
    shift = str_to_shift.at(shift_str);
    return is;
}

const std::map<Shift, std::string> shift_to_str {
    {Shift::I, "I"},
    {Shift::II, "II"},
    {Shift::III, "III"}
};

const std::map<std::string, Shift> str_to_shift {
    {"I", Shift::I},
    {"II", Shift::II},
    {"III", Shift::III}
};

std::ostream& operator<<(std::ostream& os, WorkerType type)
{
    return os << wtype_to_str.at(type);
}

std::istream& operator>>(std::istream& is, WorkerType& type)
{
    std::string type_str;
    std::cin >> type_str;
    type = str_to_wtype.at(type_str);
    return is;
}

const std::map<WorkerType, std::string> wtype_to_str {
    {WorkerType::Cook, "Cook"},
    {WorkerType::Maid, "Maid"},
    {WorkerType::Receptionist, "Receptionist"},
    {WorkerType::Waiter, "Waiter"}
};

const std::map<std::string, WorkerType> str_to_wtype {
    {"Cook", WorkerType::Cook},
    {"Maid", WorkerType::Maid},
    {"Receptionist", WorkerType::Receptionist},
    {"Waiter", WorkerType::Waiter}
};
