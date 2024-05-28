#ifndef GUEST_SYSTEM_HPP
#define GUEST_SYSTEM_HPP

#include "../types/guest.hpp"
#include <vector>
#include <optional>

class HotelSystem;

class GuestSystem
{
    public:
        GuestSystem() = default;
        void add_guest(const Guest&);
        void remove_guest(const Guest&) noexcept;
        std::optional<const Guest*> find_by_id(const std::string& id) const noexcept;
        const Guest& get_by_id(const std::string& id) const;
        const std::vector<Guest>& get_guests() const noexcept;
    private:
        std::vector<Guest> guests;
};

#endif