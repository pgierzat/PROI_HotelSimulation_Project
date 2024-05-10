#include "guest_system.hpp"
#include <algorithm>

void GuestSystem::add_guest(const Guest& guest)
{
    auto p = std::ranges::find(guests, guest);
    if (p != guests.end())
        throw std::invalid_argument("Tried to add duplicate Guest.");
    guests.push_back(guest);
}

void GuestSystem::remove_guest(const Guest& guest) noexcept { std::erase(guests, guest); }

std::optional<Guest> GuestSystem::find_by_name(const std::string& name) const noexcept
{
    auto p = std::ranges::find_if(guests,
        [&](const auto& guest){ return guest.get_name() == name; });
    if (p == guests.end())
        return std::nullopt;
    return *p;
}

bool GuestSystem::has_guest(const Guest& guest) const noexcept
{
    auto p = std::ranges::find(guests, guest);
    if (p == guests.end())
        return false;
    return true;
}

const std::vector<Guest> GuestSystem::get_guests() const noexcept { return guests; }
