#ifndef GUEST_SYSTEM_HPP
#define GUEST_SYSTEM_HPP

#include "../types/guest.hpp"
#include <vector>


class GuestSystem
{
    public:
        GuestSystem() = default;
    private:
        std::vector<Guest> guests;
};

#endif