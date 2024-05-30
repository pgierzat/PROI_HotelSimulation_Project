#include "receptionist.hpp"
#include <map>
#include <stdexcept>

unsigned Receptionist::shifts = 3;

const Amount Receptionist::penalty{10, 0};

const jed_utils::timespan Receptionist::shift_duration = jed_utils::timespan(0, 8);

const std::map<Shift, jed_utils::timespan> Receptionist::shifts_to_hours = {
    {Shift::I, jed_utils::timespan(0, 6)},
    {Shift::II, jed_utils::timespan(0, 14)},
    {Shift::III, jed_utils::timespan(0, 22)}
};

Receptionist::Receptionist(std::string id, std::string name, const Pay& pay) : Worker{id, name, pay} {}

Amount Receptionist::calculate_paycheck(unsigned hours_worked) const noexcept
{
    Amount base = calculate_base_paycheck(hours_worked);
    return base -= penalty * complaints;
}

WorkerType Receptionist::get_type() const noexcept { return type; }

unsigned Receptionist::get_shifts() const noexcept { return shifts; }

jed_utils::timespan Receptionist::get_shift_start(Shift shift) const
{
    if ( (unsigned char)(shift) > shifts )
        throw std::invalid_argument("There is no such shift for those workers.");
    return shifts_to_hours.at(shift);
}

jed_utils::timespan Receptionist::get_shift_duration() const noexcept { return shift_duration; }

unsigned Receptionist::get_complaints() const noexcept { return complaints; }

void Receptionist::set_complaints(unsigned complaints) noexcept { this -> complaints = complaints; }

void Receptionist::reset_stats() { complaints = 0; }
