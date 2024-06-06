#ifndef STAY_SYSTEM_HPP
#define STAY_SYSTEM_HPP

#include "../auxiliary/other_system_observer.hpp"
#include "../types/stay.hpp"
#include "../utilities/errors.hpp"

class HotelSystem;
class RoomsList;
class GuestSystem;

class StaySystem : public OtherSystemObserver<Room>, public OtherSystemObserver<Guest>
{
        using RObserver = OtherSystemObserver<Room>;
        using GObserver = OtherSystemObserver<Guest>;
    public:
        StaySystem(GuestSystem&, RoomsList&);
        void set_time(const jed_utils::datetime&);
        void add_stay(const Stay&);
        void remove_stay(const Stay&);
        std::optional<const Stay*> find_by_id(const std::string&) const noexcept;
        const Stay& get_by_id(const std::string&) const;
        const std::vector<Stay>& get_stays() const noexcept;
        void add_guest_to_stay(const Stay&, const Guest&);
        void check_in(const Stay&);
        void check_out(const Stay&);
        void notify_realloc(dummy<Room>) override;
        void notify_erase(const std::string& erased_obj_id, dummy<Room>) override;
        void notify_realloc(dummy<Guest>) override;
        void notify_erase(const std::string& erased_obj_id, dummy<Guest>) override;
        bool check_room(const Room&) const;
        static const jed_utils::timespan checkout_time;
        static const jed_utils::timespan checkin_time;
    private:
        std::optional<Stay*> find_stay(const Stay&) const noexcept;
        Stay& get_stay(const Stay&) const;
        void check_overlap(const Stay&) const;
        const GuestSystem* g_system;
        const RoomsList* rooms_list;
        std::vector<Stay> stays;
        jed_utils::datetime time{1970, 1, 1};
};


#endif
