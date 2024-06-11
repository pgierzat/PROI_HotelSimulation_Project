#ifndef OTHER_SYSTEM_PUBLISHER_HPP
#define OTHER_SYSTEM_PUBLISHER_HPP

#include <vector>
#include <algorithm>
#include "other_system_observer.hpp"

template<typename T>
class OtherSystemPublisher
{
    public:
        void subscribe(OtherSystemObserver<T>&);
    protected:
        void publish_erase(const std::string& erased_id);
        std::vector<OtherSystemObserver<T>*> observers;
};

template<typename T>
void OtherSystemPublisher<T>::publish_erase(const std::string& erased_id)
{
    std::ranges::for_each(observers, [&](auto& obs){ obs -> notify_erase(erased_id, dummy<T>{}); });
}

template<typename T>
void OtherSystemPublisher<T>::subscribe(OtherSystemObserver<T>& observer) {
    observers.push_back(&observer);
}


#endif
