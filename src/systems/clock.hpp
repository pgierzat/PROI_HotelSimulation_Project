#ifndef CLOCK_HPP
#define CLOCK_HPP

#include "../types/datetime.h"
#include "../auxiliary/time_publisher.hpp"


class Clock : public TimePublisher
{
    public:
        explicit Clock() = default;
        explicit Clock(jed_utils::datetime init_time);
        const jed_utils::datetime& get_time() const noexcept override;
        jed_utils::timespan get_unit_delta() const noexcept;
        void set_time(const jed_utils::datetime&);
        void set_unit_delta(const jed_utils::timespan&);
        Clock& operator+=(const jed_utils::timespan&);
        Clock& operator++();
        void publish(const jed_utils::datetime&) const;
        bool operator==(const Clock&);
    private:
        jed_utils::datetime time{1970, 1, 1};
        jed_utils::timespan unit_delta{1};
};

#endif
