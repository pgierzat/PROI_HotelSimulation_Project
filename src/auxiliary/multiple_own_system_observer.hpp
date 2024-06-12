#ifndef MULTIPLE_OWN_SYSTEM_OBSERVER_HPP
#define MULTIPLE_OWN_SYSTEM_OBSERVER_HPP

#include <optional>
#include "../auxiliary/own_system_observer.hpp"
#include "../auxiliary/weak_multiple_own_system_observer.hpp"
#include "../utilities/errors.hpp"
#include "../functions/vec_to_pvec.hpp"

template<typename T>
class MultipleOwnSystemObserver : public virtual WeakMultipleOwnSystemObserver<T>
{
    public:
        MultipleOwnSystemObserver() = default;
        MultipleOwnSystemObserver(const MultipleOwnSystemObserver<T>&);
        MultipleOwnSystemObserver(const MultipleOwnSystemObserver<T>&&);
        void notify_realloc(const T& new_obj) override;
        void notify_erase(const std::string& erased_id) noexcept override;
        std::vector<const std::string*> get_observed_ids() const noexcept override;
        bool has_id(const std::string&) const noexcept override;
        unsigned size() const noexcept;
        void add_observed(const T&);
        void remove_observed(const std::string&) noexcept;
        void remove_observed(const T&) noexcept;
        void remove_all_observed() noexcept;
        std::vector<const T*> get() const;
        const T& front() const;
        std::optional<const T*> find_by_id(const std::string&) const;
        const T& get_by_id(const std::string&) const;
    private:
            using OSO = OwnSystemObserver<T>;
        std::optional<OSO*> find_observer(const std::string& id);
        OSO& get_observer(const std::string& id);
        std::vector<std::unique_ptr<OSO>> observers;
};


template<typename T>
MultipleOwnSystemObserver<T>::MultipleOwnSystemObserver(const MultipleOwnSystemObserver<T>& other)
{
    for (const auto& obs : other.observers)
    {
        auto to_add = std::make_unique<OSO>(*obs);
        observers.emplace_back(std::move(to_add));
    }
}

template<typename T>
MultipleOwnSystemObserver<T>::MultipleOwnSystemObserver(const MultipleOwnSystemObserver<T>&& other) :
    observers{std::move(other.observers)} {}

template<typename T>
void MultipleOwnSystemObserver<T>::notify_realloc(const T& new_obj)
{
    get_observer(new_obj.get_id()).notify_realloc(new_obj);
}

template<typename T>
void MultipleOwnSystemObserver<T>::notify_erase(const std::string& erased_id) noexcept
{
    get_observer(erased_id).notify_erase();
}

template<typename T>
std::vector<const std::string*> MultipleOwnSystemObserver<T>::get_observed_ids() const noexcept
{
    auto ids = std::vector<const std::string*>{};
    std::ranges::for_each(observers, [&](const auto& obs){ ids.push_back(&obs -> get_observed_id()); });
    return ids;
}

template<typename T>
bool MultipleOwnSystemObserver<T>::has_id(const std::string& id) const noexcept
{
    auto p = std::ranges::find_if(observers,
        [&](const auto& obs){ return obs -> get_observed_id() == id; });
    return p != observers.end();
}

template<typename T>
unsigned MultipleOwnSystemObserver<T>::size() const noexcept { return observers.size(); }

template<typename T>
void MultipleOwnSystemObserver<T>::remove_observed(const std::string& id) noexcept
{
    std::erase_if(observers, [&](const auto& obs){ return obs -> get_observed_id() == id; });
}

template<typename T>
std::vector<const T*> MultipleOwnSystemObserver<T>::get() const
{
    auto observed = std::vector<const T*>{};
    std::ranges::for_each(observers, [&](const auto& obs){ observed.push_back(&obs -> get()); });
    return observed;
}

template<typename T>
const T& MultipleOwnSystemObserver<T>::front() const { return observers.front() -> get(); }

template<typename T>
std::optional<const T*> MultipleOwnSystemObserver<T>::find_by_id(const std::string& id) const
{
    auto p = std::ranges::find_if(observers,
        [&](const auto& obs){ return obs -> get_observed_id() == id; });
    if (p != observers.end())
        return std::nullopt;
    return &p -> get() -> get();
}

template<typename T>
const T& MultipleOwnSystemObserver<T>::get_by_id(const std::string& id) const
{
    auto p = std::ranges::find_if(observers,
        [&](const auto& obs){ return obs -> get_observed_id() == id; });
    if (p == observers.end())
        throw MultipleOwnSystemObserverError<T>("Couldn't get observed object by id.", *this);
    return p -> get() -> get();
}

template<typename T>
void MultipleOwnSystemObserver<T>::add_observed(const T& obj)
{
    if (find_observer(obj.get_id()))
        throw MultipleOwnSystemObserverError<T>("Tried to add duplicate observed object.", *this);
    auto to_add = std::make_unique<OSO>(obj);
    observers.emplace_back(std::move(to_add));
}

template<typename T>
void MultipleOwnSystemObserver<T>::remove_observed(const T& obj) noexcept
{
    std::erase_if(observers, [&](const auto& obs){ return obs -> get_observed_id() == obj.get_id(); });
}

template<typename T>
void MultipleOwnSystemObserver<T>::remove_all_observed() noexcept
{
    observers.clear();
}

template<typename T>
std::optional<OwnSystemObserver<T>*> MultipleOwnSystemObserver<T>::find_observer(const std::string& id)
{
    auto p = std::ranges::find_if(observers,
        [&](const auto& obs){ return obs -> get_observed_id() == id; });
    if (p == observers.end())
        return std::nullopt;
    return  p -> get();
}

template<typename T>
OwnSystemObserver<T>& MultipleOwnSystemObserver<T>::get_observer(const std::string& id)
{
    auto p = std::ranges::find_if(observers,
        [&](const auto& obs){ return obs -> get_observed_id() == id; });
    if (p == observers.end())
        throw MultipleOwnSystemObserverError<T>("Couldn't find observer among MOSObserver's observers.", *this);
    return **p;
}


#endif
