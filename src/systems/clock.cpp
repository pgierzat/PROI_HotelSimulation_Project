#include "clock.hpp"
#include <algorithm>


Clock::Clock(jed_utils::datetime init_time) : time{init_time} {}

const jed_utils::datetime& Clock::get_time() const noexcept { return time; }

jed_utils::timespan Clock::get_unit_delta() const noexcept { return unit_delta; }

void Clock::set_time(const jed_utils::datetime& time)
{
    if (time < this -> time)
        throw std::invalid_argument("can't decrese clock's time.");
    this -> time = time;
    publish(time);
}

void Clock::set_unit_delta(const jed_utils::timespan& unit_delta) { this -> unit_delta = unit_delta; }

Clock& Clock::operator+=(const jed_utils::timespan& delta)
{
    time += delta;
    publish(time);
    return *this;
}

Clock& Clock::operator++()
{
    time += unit_delta;
    publish(time);
    return *this;
}

void Clock::publish(const jed_utils::datetime& time) const
{
    std::ranges::for_each(observers, [&](auto obs){ obs -> notify(time); });
}

bool Clock::operator==(const Clock& other) { return time == other.time; }
