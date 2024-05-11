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
        void set_time(const jed_utils::datetime&);
        void add_stay(const Stay&);
        void remove_stay(const Stay&);
        const std::vector<Stay>& get_stays() const noexcept;
        std::vector<const Stay*> get_active_stays() const noexcept;
        std::vector<const Stay*> get_ending_stays() const noexcept;
        static const jed_utils::timespan checkout_time;
        static const jed_utils::timespan checkin_time;
    private:
        void refresh_active_stays();
        void refresh_ending_stays(const std::vector<Stay*>& previous_stays);
        void check_overlap(const Stay&);
        void validate_guest(const Guest&);
        void validate_guests(const Stay&); 
        void validate_room(const Room&); 
        const GuestSystem* g_system = nullptr;
        const RoomsList* rooms_list = nullptr;
        std::vector<Stay> stays;
        std::vector<Stay*> active_stays;
        std::vector<Stay*> ending_stays;
        jed_utils::datetime time{1970, 1, 1};
};


#endif
