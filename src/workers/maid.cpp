#include "maid.hpp"
#include <string>
#include <stdexcept>


unsigned Maid::workers_per_shift = 3;

const Amount Maid::bonus{1, 50};

const jed_utils::timespan Maid::shift_duration = jed_utils::timespan(0, 6);

const std::map<Shift, jed_utils::timespan> Maid::shifts_to_hours = {
    {Shift::I, jed_utils::timespan(0, 8)},
    {Shift::II, jed_utils::timespan(0, 14)}
};

Maid::Maid(std::string id, std::string name, const Pay& pay) : Worker{id, name, pay} {}

Amount Maid::calculate_paycheck(unsigned hours_worked) const noexcept
{
    Amount base = calculate_base_paycheck(hours_worked);
    return base += bonus * rooms_serviced;
}

WorkerType Maid::get_type() const noexcept { return type; }

unsigned Maid::get_shifts() const noexcept { return shifts; }

unsigned Maid::get_workers_per_shift() const noexcept { return workers_per_shift; }

jed_utils::timespan Maid::get_shift_start(Shift shift) const
{
    if ( (unsigned char)(shift) > shifts )
        throw std::invalid_argument("There is no such shift for those workers.");
    return shifts_to_hours.at(shift);
}

jed_utils::timespan Maid::get_shift_duration() const noexcept { return shift_duration; }

unsigned Maid::get_rooms_serviced() const noexcept { return rooms_serviced; }

void Maid::set_rooms_serviced(unsigned rooms_serviced) noexcept { this -> rooms_serviced = rooms_serviced; }

void Maid::reset_stats() { rooms_serviced = 0; }

const Amount& Maid::get_bonus() { return bonus; }

void Maid::set_workers_per_shift(unsigned workers_per_shift) {
    Maid::workers_per_shift = workers_per_shift;
}
