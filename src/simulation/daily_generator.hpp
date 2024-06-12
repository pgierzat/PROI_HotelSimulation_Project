#ifndef DAILY_GENERATOR_HPP
#define DAILY_GENERATOR_HPP

#include "../types/datetime.h"
#include "../types/timespan.h"
#include "../auxiliary/time_observer.hpp"
#include "../auxiliary/time_publisher.hpp"

class DailyGenerator : public TimeObserver
{
        using datetime = jed_utils::datetime;
        using timespan = jed_utils::timespan;
    public:
        DailyGenerator(TimePublisher&, const timespan& time_of_gen);
        virtual ~DailyGenerator() = default;
        void notify(const datetime&) override;
    protected:
        virtual void generate() = 0;
        virtual void set_time_next() noexcept;
        virtual void initiate_time_next() noexcept;
        datetime time;
        datetime time_next;
        timespan time_of_gen;
};

#endif
