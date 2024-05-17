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

TimeInterval TimeInterval::month_to_interval(std::chrono::year_month year_month)
{
    std::chrono::year_month_day first = year_month / std::chrono::day{1};
    std::chrono::year_month_day last = year_month / std::chrono::last;
    jed_utils::datetime start{first};
    jed_utils::datetime stop{last};
    return TimeInterval{start, stop};
}

jed_utils::timespan distance(const TimeInterval& i1, const TimeInterval& i2)
{
    return std::max({ i2.get_start() - i1.get_end(), i1.get_start() - i2.get_end() });
}

bool is_in(const jed_utils::datetime time, const TimeInterval& interval)
{
    return interval.get_start() <= time && time <= interval.get_end();
}
