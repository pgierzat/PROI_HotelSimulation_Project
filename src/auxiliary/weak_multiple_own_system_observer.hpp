#ifndef WEAK_MULTIPLE_OWN_SYSTEM_OBSERVER_HPP
#define WEAK_MULTIPLE_OWN_SYSTEM_OBSERVER_HPP

#include <vector>
#include <memory>
#include <algorithm>
#include "weak_own_system_observer.hpp"

template<typename T>
class WeakMultipleOwnSystemObserver
{
    public:
            using WOSO = WeakOwnSystemObserver<T>;
        WeakMultipleOwnSystemObserver() = default;
        WeakMultipleOwnSystemObserver(const WeakMultipleOwnSystemObserver&) = delete;
        virtual void notify_realloc(const T& new_obj);
        virtual void notify_erase(const std::string& erased_id) noexcept;
        std::vector<const std::string*> get_ids() const noexcept;
        bool has_id(const std::string&) const noexcept;
        unsigned size() const noexcept;
        void add_observed_id(const std::string&);
        void remove_observed(const std::string&) noexcept;
    protected:
        std::vector<std::unique_ptr<WOSO>> observers;
};

template<typename T>
void WeakMultipleOwnSystemObserver<T>::notify_realloc(const T& new_obj) {}

template<typename T>
void WeakMultipleOwnSystemObserver<T>::notify_erase(const std::string& erased_id) noexcept {}

template<typename T>
std::vector<const std::string*> WeakMultipleOwnSystemObserver<T>::get_ids() const noexcept
{
    auto ids = std::vector<const std::string*>{};
    std::ranges::for_each(observers, [&](const auto& obs){ ids.push_back(&obs -> get_id()); });
    return ids;
}

template<typename T>
bool WeakMultipleOwnSystemObserver<T>::has_id(const std::string& id) const noexcept
{
    auto p = std::ranges::find_if(observers, [&](const auto& obs){ return obs -> get_id() == id; });
    return p != observers.end();
}

template<typename T>
unsigned WeakMultipleOwnSystemObserver<T>::size() const noexcept { return observers.size(); }

template<typename T>
void WeakMultipleOwnSystemObserver<T>::add_observed_id(const std::string& id)
{
    auto p = std::ranges::find_if(observers, [&](const auto& obs){ return obs -> get_id() == id; });
    if (p != observers.end())
        throw std::invalid_argument("Tried to add duplicate id to WMOSO.");
    auto to_add = std::make_unique<WOSO>(id);
    observers.emplace_back(to_add);
}

template<typename T>
void WeakMultipleOwnSystemObserver<T>::remove_observed(const std::string& id) noexcept
{
    std::erase_if(observers, [&](const auto& obs){ return obs.get_id() == id; });
}


#endif
