#ifndef PSEUDO_MULTIPLE_OWN_SYSTEM_OBSERVER_HPP
#define PSEUDO_MULTIPLE_OWN_SYSTEM_OBSERVER_HPP

#include "weak_multiple_own_system_observer.hpp"
#include <vector>
#include <memory>
#include <algorithm>
#include "weak_own_system_observer.hpp"

template<typename T>
class PseudoMultipleOwnSystemObserver : public virtual WeakMultipleOwnSystemObserver<T>
{
    public:
        void notify_realloc(const T& new_obj) override;
        void notify_erase(const std::string& erased_id) noexcept override;
        std::vector<const std::string*> get_observed_ids() const noexcept override;
        bool has_id(const std::string&) const noexcept override;
};


template<typename T>
void PseudoMultipleOwnSystemObserver<T>::notify_realloc(const T& new_obj) {}

template<typename T>
void PseudoMultipleOwnSystemObserver<T>::notify_erase(const std::string& erased_id) noexcept {}

template<typename T>
std::vector<const std::string*> PseudoMultipleOwnSystemObserver<T>::get_observed_ids() const noexcept {
    return std::vector<const std::string*>{};
}

template<typename T>
bool PseudoMultipleOwnSystemObserver<T>::has_id(const std::string&) const noexcept {
    return false;
}


#endif
