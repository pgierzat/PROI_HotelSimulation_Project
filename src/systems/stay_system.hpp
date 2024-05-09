#ifndef STAY_SYSTEM_HPP
#define STAY_SYSTEM_HPP

#include "../types/stay.hpp"
#include "../rooms/hpp/rooms_list.hpp"


class StaySystem
{
    public:
        StaySystem() = default;
        void bind_guest_system(const GuestSystem&);
        void bind_room_system(const RoomsList&); 
    private:
        GuestSystem* g_system = nullptr;
        RoomsList* rooms_list = nullptr;
};

#endif
