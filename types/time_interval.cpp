#include "time_interval.hpp"
#include <stdexcept>

TimeInterval::TimeInterval(jed_utils::datetime start, jed_utils::datetime end) : start{start}, end{end}
{
    if (start > end)
        throw std::invalid_argument("time_interval's start > end.");
}

jed_utils::datetime TimeInterval::get_start() const noexcept { return start; }

jed_utils::datetime TimeInterval::get_end() const noexcept { return end; }

jed_utils::timespan TimeInterval::get_duration() const noexcept { return end - start; };

jed_utils::timespan distance(const TimeInterval& i1, const TimeInterval& i2)
{
    return std::max({ i2.get_start() - i1.get_end(), i1.get_start() - i2.get_end() });
}
