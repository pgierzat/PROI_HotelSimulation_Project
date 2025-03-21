#ifndef STAY_HPP
#define STAY_HPP

#include <vector>
#include "../rooms/hpp/room.hpp"
#include "amount.hpp"
#include "datetime.h"
#include "timespan.h"
#include "guest.hpp"
#include "time_interval.hpp"
#include "../auxiliary/own_system_observer.hpp"
#include "../auxiliary/multiple_own_system_observer.hpp"



class StaySystem;
class GuestSystem;
class RoomsList;

enum class StayStatus : unsigned {
    booked,
    checked_in,
    checked_out
};


class Stay : protected OwnSystemObserver<Room>, protected MultipleOwnSystemObserver<Guest>
{
            using wRoomObs = WeakOwnSystemObserver<Room>;
            using wGuestsObs = WeakMultipleOwnSystemObserver<Guest>;
            using RoomObs = OwnSystemObserver<Room>;
            using GuestsObs = MultipleOwnSystemObserver<Guest>;
    public:
        Stay(const std::string& id, const Room&, const Guest& main_guest,
            const jed_utils::datetime& start, const jed_utils::datetime& end);
        const std::string& get_id() const noexcept;
        const std::vector<const Guest*> get_guests() const;
        const Guest& get_main_guest() const;
        const Room& get_room() const;
        jed_utils::datetime get_start() const noexcept;
        jed_utils::datetime get_start_date() const noexcept;
        jed_utils::datetime get_end() const noexcept;
        jed_utils::datetime get_end_date() const noexcept;
        TimeInterval get_interval() const noexcept;
        Amount get_price() const;
        unsigned get_duration() const noexcept;
        StayStatus get_status() const noexcept;
        void add_guest(const Guest&);
        void remove_guest(const Guest&);
        void set_id(const std::string& id) noexcept;
        void set_start(jed_utils::datetime start);
        void set_end(jed_utils::datetime end);
        void set_status(StayStatus);
        bool operator==(const Stay&) const;
        static const jed_utils::timespan checkout_time;
        static const jed_utils::timespan checkin_time;
    protected:
        static void validate_duration(const jed_utils::datetime& start, const jed_utils::datetime& end);
        std::string id;
        jed_utils::datetime start;
        jed_utils::datetime end;
        StayStatus status{StayStatus::booked};
};

#endif
