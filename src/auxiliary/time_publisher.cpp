#include "time_publisher.hpp"
#include <ranges>

void TimePublisher::subscribe(TimeObserver& observer)
{
    observers.push_back(&observer);
}
