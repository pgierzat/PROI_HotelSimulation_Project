#ifndef STAY_SYSTEM_HPP
#define STAY_SYSTEM_HPP

#include "../types/stay.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "guest_system.hpp"


class StaySystem
{
    public:
        StaySystem() = default;
        void bind_guest_system(const GuestSystem&);
        void bind_room_system(const RoomsList&); 
        void add_stay(const Stay&);
        void remove_stay(const Stay&);
        std::vector<Stay> get_stays() const noexcept;
        static const jed_utils::timespan minimal_break;
    private:
        const GuestSystem* g_system = nullptr;
        const RoomsList* rooms_list = nullptr;
        std::vector<Stay> stays;
};

#endif
