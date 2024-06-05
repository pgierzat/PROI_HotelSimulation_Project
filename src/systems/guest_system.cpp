#include "guest_system.hpp"
#include "../utilities/errors.hpp"
#include <algorithm>

void GuestSystem::add_guest(const Guest& guest)
{
    const auto& id = guest.get_id();
    auto p = std::ranges::find_if(guests,
        [&](const auto& otr_guest){ return otr_guest.get_id() == id; });
    if (p != guests.end())
        throw std::invalid_argument("Tried to add Guest with duplicate id.");
    auto p1 = guests.begin();
    guests.push_back(guest);
    if (p1 != guests.begin())
        publish_realloc();
}

void GuestSystem::remove_guest(const Guest& guest) noexcept
{
    std::erase(guests, guest);
    publish_erase(guest.get_id());
    publish_realloc();
}

std::optional<const Guest*> GuestSystem::find_by_id(const std::string& id) const noexcept
{
    auto p = std::ranges::find_if(guests,
        [&](const auto& guest){ return guest.get_id() == id; });
    if (p == guests.end())
        return std::nullopt;
    return &*p;
}

const Guest& GuestSystem::get_by_id(const std::string& id) const
{
    auto p = std::ranges::find_if(guests,
        [&](const auto& guest){ return guest.get_id() == id; });
    if (p == guests.end())
        throw GuestNotInSystemError("GuestSystem::get_by_id failed.", id);
    return *p;
}

const std::vector<Guest>& GuestSystem::get_guests() const noexcept { return guests; }
