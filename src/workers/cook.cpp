#include "cook.hpp"
#include <string>
#include <stdexcept>


unsigned Cook::workers_per_shift = 1;

const Amount Cook::bonus{1, 0};

const jed_utils::timespan Cook::shift_duration = jed_utils::timespan(0, 12);

const std::map<Shift, jed_utils::timespan> Cook::shifts_to_hours = {
    {Shift::I, jed_utils::timespan(0, 8)},
};

Cook::Cook(std::string id, std::string name, const Pay& pay) : Worker{id, name, pay} {}

Amount Cook::calculate_paycheck(unsigned hours_worked) const noexcept
{
    Amount base = calculate_base_paycheck(hours_worked);
    return base += bonus * dishes_prepared;
}

WorkerType Cook::get_type() const noexcept { return type; }

unsigned Cook::get_shifts() const noexcept { return shifts; }

unsigned Cook::get_workers_per_shift() const noexcept { return workers_per_shift; }

jed_utils::timespan Cook::get_shift_start(Shift shift) const
{
    if ( (unsigned char)(shift) > shifts )
        throw std::invalid_argument("There is no such shift for those workers.");
    return shifts_to_hours.at(shift);
}

jed_utils::timespan Cook::get_shift_duration() const noexcept { return shift_duration; }

unsigned Cook::get_dishes_prepared() const noexcept { return dishes_prepared; }

void Cook::set_dishes_prepared(unsigned dishes_prepared) noexcept { this -> dishes_prepared = dishes_prepared; }

void Cook::reset_stats() { dishes_prepared = 0; }

const Amount& Cook::get_bonus() { return bonus; }

void Cook::set_workers_per_shift(unsigned workers_per_shift) {
    Cook::workers_per_shift = workers_per_shift;
}
