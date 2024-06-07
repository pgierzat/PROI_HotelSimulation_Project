#ifndef TIME_PUBLISHER_HPP
#define TIME_PUBLISHER_HPP

#include "../types/datetime.h"
#include "time_observer.hpp"
#include <vector>


class TimePublisher
{
    public:
        virtual void publish(const jed_utils::datetime&) const = 0;
        void subscribe(TimeObserver&);
        virtual const jed_utils::datetime& get_time() const noexcept = 0;
    protected:
        std::vector<TimeObserver*> observers;
};

#endif
