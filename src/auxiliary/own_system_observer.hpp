#ifndef OWN_SYSTEM_OBSERVER_HPP
#define OWN_SYSTEM_OBSERVER_HPP

#include "../utilities/errors.hpp"
#include "weak_own_system_observer.hpp"

template<typename T>
class OwnSystemObserver : public virtual WeakOwnSystemObserver<T>
{
    public:
            using WeakObs = WeakOwnSystemObserver<T>;
        OwnSystemObserver() = default;
        explicit OwnSystemObserver(const T& observed);
        void notify_realloc(const T& new_obj) override;
        void notify_erase() noexcept override;
        const std::string& get_observed_id() const noexcept override;
        const T& get() const;
        explicit operator bool() const noexcept;
        bool has_value() const noexcept;
        void set(const T&);
        void reset() noexcept;
    private:
        std::string observed_id;
        const T* observed = nullptr;
};


template<typename T>
OwnSystemObserver<T>::OwnSystemObserver(const T& obj) : observed_id{obj.get_id()}, observed{&obj} {}

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
const std::string& OwnSystemObserver<T>::get_observed_id() const noexcept { return observed_id; }

template<typename T>
const T& OwnSystemObserver<T>::get() const
{
    if (not observed)
        throw OwnSystemObserverError<T>("Tried to access observed object of an 'empty' observer.", *this);
    return *observed;
}

template<typename T>
void OwnSystemObserver<T>::set(const T& obj)
{
    observed_id = obj.get_id();
    observed = &obj;
}

template<typename T>
void OwnSystemObserver<T>::reset() noexcept
{
    observed = nullptr;
    observed_id = "";
}

template<typename T>
OwnSystemObserver<T>::operator bool() const noexcept { return observed; }

template<typename T>
bool OwnSystemObserver<T>::has_value() const noexcept { return observed; }


#endif
