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
    protected:
        std::vector<TimeObserver*> observers;
};

#endif
