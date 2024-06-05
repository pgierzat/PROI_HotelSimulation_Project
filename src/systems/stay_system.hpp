#ifndef STAY_SYSTEM_HPP
#define STAY_SYSTEM_HPP

#include "../types/stay.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "guest_system.hpp"


class StaySystem
{
    public:
        StaySystem(const GuestSystem&, const RoomsList&);
        const GuestSystem& get_cguest_system() const;
        const RoomsList& get_crooms_list() const;
        void set_time(const jed_utils::datetime&);
        void add_stay(const Stay&);
        void remove_stay(const Stay&);
        std::optional<const Stay*> find_by_id(const std::string&) const noexcept;
        const Stay& get_by_id(const std::string&) const;
        const std::vector<Stay>& get_stays() const noexcept;
        void check_in(const Stay&);
        void check_out(const Stay&);
        bool check_room(const Room&) const noexcept;
        static const jed_utils::timespan checkout_time;
        static const jed_utils::timespan checkin_time;
    private:
        std::optional<Stay*> get_stay(const Stay&) const noexcept;
        Stay& validate_stay(const Stay&) const;
        void check_overlap(const Stay&) const;
        const GuestSystem* g_system;
        const RoomsList* rooms_list;
        std::vector<Stay> stays;
        jed_utils::datetime time{1970, 1, 1};
};


#endif
