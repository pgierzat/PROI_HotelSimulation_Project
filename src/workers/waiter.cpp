#include "waiter.hpp"
#include <string>
#include <stdexcept>


unsigned Waiter::workers_per_shift = 2;

const Amount Waiter::bonus{2, 0};

const jed_utils::timespan Waiter::shift_duration = jed_utils::timespan(0, 12);

const std::map<Shift, jed_utils::timespan> Waiter::shifts_to_hours = {
    {Shift::I, jed_utils::timespan(0, 8)},
};

Waiter::Waiter(std::string id, std::string name, const Pay& pay) : Worker{id, name, pay} {}

Amount Waiter::calculate_paycheck(unsigned hours_worked) const noexcept
{
    Amount base = calculate_base_paycheck(hours_worked);
    return base += bonus * orders_taken;
}

WorkerType Waiter::get_type() const noexcept { return type; }

unsigned Waiter::get_shifts() const noexcept { return shifts; }

unsigned Waiter::get_workers_per_shift() const noexcept { return workers_per_shift; }

jed_utils::timespan Waiter::get_shift_start(Shift shift) const
{
    if ( (unsigned char)(shift) > shifts )
        throw std::invalid_argument("There is no such shift for those workers.");
    return shifts_to_hours.at(shift);
}

jed_utils::timespan Waiter::get_shift_duration() const noexcept { return shift_duration; }

unsigned Waiter::get_orders_taken() const noexcept { return orders_taken; }

void Waiter::set_orders_taken(unsigned orders_taken) noexcept { this -> orders_taken = orders_taken; }

void Waiter::reset_stats() { orders_taken = 0; }

const Amount& Waiter::get_bonus() { return bonus; }

void Waiter::set_workers_per_shift(unsigned workers_per_shift) {
    Waiter::workers_per_shift = workers_per_shift;
}
