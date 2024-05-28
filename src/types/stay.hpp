#ifndef STAY_HPP
#define STAY_HPP

#include "../rooms/hpp/room.hpp"
#include "amount.hpp"
#include "datetime.h"
#include "timespan.h"
#include "guest.hpp"
#include "time_interval.hpp"
#include <vector>


class StaySystem;
class GuestSystem;
class RoomsList;

enum class StayStatus : unsigned {
    booked,
    checked_in,
    checked_out
};


class Stay
{
    public:
        Stay(const std::string& id, const Room&, const Guest& main_guest, const jed_utils::datetime& start,
             const jed_utils::datetime& end);
        const std::string& get_id() const noexcept;
        const std::vector<const Guest*> get_guests() const;
        const Guest& get_main_guest() const;
        const Room& get_room() const;
        jed_utils::datetime get_start() const noexcept;
        jed_utils::datetime get_end() const noexcept;
        TimeInterval get_interval() const noexcept;
        Amount get_price() const;
        unsigned get_duration() const noexcept;
        StayStatus get_status() const noexcept;
        void add_guest(const Guest&);
        void remove_guest(const Guest&);
        void set_start(const jed_utils::datetime start);
        void set_end(const jed_utils::datetime end);
        void set_status(StayStatus);
        bool operator==(const Stay&) const;
        static void set_s_system(const StaySystem&);
        static void set_g_system(const GuestSystem&);
        static void set_rooms_list(const RoomsList&);
    private:
        static const StaySystem* s_system;
        static const GuestSystem* g_system;
        static const RoomsList* rooms_list;
        static void validate_duration(const jed_utils::datetime& start, const jed_utils::datetime& end);
        std::vector<std::string> guests_ids;
        std::string main_guest_id;    // Guest that pays for everything
        std::string id;
        jed_utils::datetime start;
        jed_utils::datetime end;
        unsigned room_nr;
        StayStatus status{StayStatus::booked};
};

#endif
