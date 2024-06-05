#ifndef OTHER_SYSTEM_OBSERVER_HPP
#define OTHER_SYSTEM_OBSERVER_HPP

#include "../utilities/errors.hpp"

template<typename T>
class dummy {};

template<typename T>
class OtherSystemObserver
{
    public:
        virtual ~OtherSystemObserver() {};
        virtual void notify_realloc(dummy<T>) = 0;
        virtual void notify_erase(const std::string& erased_obj_id, dummy<T>) = 0;
};


#endif
