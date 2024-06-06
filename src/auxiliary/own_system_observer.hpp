#ifndef OWN_SYSTEM_OBSERVER_HPP
#define OWN_SYSTEM_OBSERVER_HPP

#include "../utilities/errors.hpp"

template<typename T>
class OwnSystemObserver
{
    public:
        OwnSystemObserver(const T& observed);
        void notify_realloc(const T& new_obj);
        void notify_erase() noexcept;
        const T& get_observed() const;
        const std::string& get_observed_id() const noexcept;
    private:
        const T* observed = nullptr;
        std::string observed_id;
};


template<typename T>
OwnSystemObserver<T>::OwnSystemObserver(const T& observed) :
    observed{&observed}, observed_id{observed.get_id()} {}

template<typename T>
void OwnSystemObserver<T>::notify_realloc(const T& new_obj)
{
    if (new_obj.get_id() != observed_id)
        throw OwnSystemObserverError<T>("Observer got different object upon deallocation of the original.", *this);
    observed = &new_obj;
}

template<typename T>
void OwnSystemObserver<T>::notify_erase() noexcept
{
    observed = nullptr;
}

template<typename T>
const T& OwnSystemObserver<T>::get_observed() const
{
    if (not observed)
        throw OwnSystemObserverError<T>("Tried to access observed object of an 'empty' observer.", *this);
    return *observed;
}

template<typename T>
const std::string& OwnSystemObserver<T>::get_observed_id() const noexcept { return observed_id; }


#endif
