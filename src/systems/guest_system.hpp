#ifndef GUEST_SYSTEM_HPP
#define GUEST_SYSTEM_HPP

#include "../types/guest.hpp"
#include <vector>


class GuestSystem
{
    public:
        GuestSystem() = default;
        void add_guest(Guest) const;
        void remove_guest(Guest) const noexcept;
        void find_by_name(const std::string& name) const noexcept;
        const std::vector<Guest> get_guests() const noexcept;
    private:
        std::vector<Guest> guests;
};

#endif