#ifndef PSEUDO_OWN_SYSTEM_OBSERVER_HPP
#define PSEUDO_OWN_SYSTEM_OBSERVER_HPP

#include <string>
#include "weak_own_system_observer.hpp"


template<typename T>
class PseudoOwnSystemObserver : public virtual WeakOwnSystemObserver<T>
{
    public:
        void notify_realloc(const T& new_obj) override;
        void notify_erase() noexcept override;
        const std::string& get_observed_id() const noexcept override;
    private:
        static const std::string empty_id;
};


template<typename T>
void PseudoOwnSystemObserver<T>::notify_realloc(const T& new_obj) {}

template<typename T>
void PseudoOwnSystemObserver<T>::notify_erase() noexcept {}

template<typename T>
const std::string& PseudoOwnSystemObserver<T>::get_observed_id() const noexcept { return empty_id; }

template<typename T>
const std::string PseudoOwnSystemObserver<T>::empty_id = "";

#endif
