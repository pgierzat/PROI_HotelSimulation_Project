#ifndef GUEST_SYSTEM_HPP
#define GUEST_SYSTEM_HPP

#include "../types/guest.hpp"
#include <vector>
#include <optional>


class GuestSystem
{
    public:
        GuestSystem() = default;
        void add_guest(const Guest&);
        void remove_guest(const Guest&) noexcept;
        std::optional<Guest> find_by_name(const std::string& name) const noexcept;
        bool has_guest(const Guest&) const noexcept;
        const std::vector<Guest> get_guests() const noexcept;
    private:
        std::vector<Guest> guests;
};

#endif