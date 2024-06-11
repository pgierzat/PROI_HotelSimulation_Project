#ifndef WEAK_OWN_SYSTEM_OBSERVER
#define WEAK_OWN_SYSTEM_OBSERVER

#include <string>


template<typename T>
class WeakOwnSystemObserver
{
    public:
        virtual ~WeakOwnSystemObserver() {};
        virtual void notify_realloc(const T& new_obj) = 0;
        virtual void notify_erase() noexcept = 0;
        virtual const std::string& get_observed_id() const noexcept = 0;
};


#endif
