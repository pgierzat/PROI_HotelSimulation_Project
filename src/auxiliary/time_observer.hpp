#ifndef TIME_OBSERVER_HPP
#define TIME_OBSERVER_HPP

#include "../types/datetime.h"



class TimeObserver
{
    public:
        virtual void notify(const jed_utils::datetime&) = 0;
};

#endif
