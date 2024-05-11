#include "clock.hpp"


explicit Clock::Clock(jed_utils::timespan unit_delta) : unit_delta{unit_delta} {}

jed_utils::datetime Clock::get_time() const noexcept { return time; }

jed_utils::timespan Clock::get_unit_delta() const noexcept { return unit_delta; }

void Clock::set_time(const jed_utils::datetime& time) { this -> time = time; }

void Clock::set_unit_delta(const jed_utils::timespan& unit_delta) { this -> unit_delta = unit_delta; }

Clock& Clock::operator+=(const jed_utils::timespan& delta)
{
    time += delta;
    return *this;
}

Clock& Clock::operator++()
{
    time += unit_delta;
    return *this;
}

Clock Clock::operator++(int)
{
    Clock old{*this};
    time += unit_delta;
    return old;
}
