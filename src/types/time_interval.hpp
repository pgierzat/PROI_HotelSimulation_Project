#include "datetime.h"
#include "timespan.h"


#ifndef TIME_INTERVAL_HPP
#define TIME_INTERVAL_HPP

class TimeInterval
{
    public:
        TimeInterval(jed_utils::datetime start, jed_utils::datetime end);
        jed_utils::datetime get_start() const noexcept;
        jed_utils::datetime get_end() const noexcept;
        jed_utils::timespan get_duration() const noexcept;
        bool operator==(const TimeInterval&) const noexcept = default;
    private:
        jed_utils::datetime start;
        jed_utils::datetime end;
};

jed_utils::timespan distance(const TimeInterval& i1, const TimeInterval& i2);

#endif
