#include "clock.hpp"


explicit Clock::Clock(jed_utils::timespan unit_delta) : unit_delta{unit_delta} {}

jed_utils::datetime Clock::get_time() const noexcept { return time; }

void Clock::set_time(const jed_utils::datetime& time) { this -> time = time; }

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
