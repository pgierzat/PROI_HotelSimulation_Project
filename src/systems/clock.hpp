#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "../types/datetime.h"


class Clock
{
    public:
        explicit Clock(jed_utils::timespan unit_delta);
        Clock() = default;
        jed_utils::datetime get_time() const noexcept;
        jed_utils::timespan get_unit_delta() const noexcept;
        void set_time(const jed_utils::datetime&);
        void set_unit_delta(const jed_utils::timespan&);
        Clock& operator+=(const jed_utils::timespan&);
        Clock& operator++();
        Clock operator++(int);
    private:
        jed_utils::datetime time{0, 0, 0};
        jed_utils::timespan unit_delta{1};
};

#endif
