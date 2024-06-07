#ifndef STAY_SYSTEM_HPP
#define STAY_SYSTEM_HPP

#include "../auxiliary/other_system_observer.hpp"
#include "../auxiliary/time_observer.hpp"
#include "../auxiliary/time_publisher.hpp"
#include "../inner_types/inner_stay.hpp"
#include "../utilities/errors.hpp"
#include <memory>

class HotelSystem;
class RoomsList;
class GuestSystem;

class StaySystem : public OtherSystemObserver<Room>, public OtherSystemObserver<Guest>, public TimeObserver
{
        using RObserver = OtherSystemObserver<Room>;
        using GObserver = OtherSystemObserver<Guest>;
    public:
        StaySystem(TimePublisher&, GuestSystem&, RoomsList&);
        StaySystem(const StaySystem&) = delete;
        void notify(const jed_utils::datetime&) override;
        void add_stay(const Stay&);
        void remove_stay(const Stay&);
        std::optional<const Stay*> find_by_id(const std::string&) const noexcept;
        const Stay& get_by_id(const std::string&) const;
        std::vector<const Stay*> get_stays() const noexcept;
        void check_in(const Stay&);
        void check_out(const Stay&);
        void notify_realloc(dummy<Room>) override;
        void notify_erase(const std::string& erased_obj_id, dummy<Room>) override;
        void notify_realloc(dummy<Guest>) override;
        void notify_erase(const std::string& erased_obj_id, dummy<Guest>) override;
        bool check_room(const Room&) const;
    private:
        std::optional<InnerStay*> find_stay(const Stay&) const noexcept;
        InnerStay& get_stay(const Stay&) const;
        void check_overlap(const Stay&) const;
        jed_utils::datetime time{1970, 1, 1};
        const GuestSystem* g_system;
        const RoomsList* rooms_list;
        std::vector<std::unique_ptr<InnerStay>> stays;
};


#endif
