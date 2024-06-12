#ifndef STAY_GENERATOR_HPP
#define STAY_GENERATOR_HPP


#include "../rooms/hpp/rooms_list.hpp"
#include "../systems/stay_system.hpp"
#include "random_generator.hpp"
#include "../auxiliary/id_generator.hpp"
#include "../functions/to_interval.hpp"
#include <random>


class StayGenerator : public RandomGenerator
{
        using datetime = jed_utils::datetime;
        using timespan = jed_utils::timespan;
    public:
        StayGenerator(HotelSystem&);
    protected:
        void generate() override;
        template<SupportedRoom T>
            std::optional<Stay> generate_stay(const std::vector<Guest>&, int days);
        std::vector<Guest> generate_guests(unsigned guests_nr);
        IDGenerator name_gen;
        std::normal_distribution<> normal_guests{2, 1};
        ToInterval<int> guests_interval{1, 4};
        std::exponential_distribution<> uniform_days{2};
        ToInterval<int> days_interval{1, 7};
        const RoomsList* rooms_list;
        StaySystem* s_system;
        GuestSystem* g_system;
};


template<SupportedRoom T>
std::optional<Stay> StayGenerator::generate_stay(const std::vector<Guest>& guests, int days)
{
    const std::list<std::unique_ptr<Room>>& rooms = rooms_list -> getRooms();
    auto& main_guest = guests.front();
    auto& start = time;
    auto end = start + jed_utils::timespan(days);
    auto it = find_if(rooms.begin(), rooms.end(), [&](const auto& room) {
        auto casted_room = dynamic_cast<T*>(room.get());
        if (not casted_room)
            return false;
        auto stay = Stay{"", *casted_room, main_guest, start, end};
        return not s_system -> does_overlap(stay);
    });
    if(it == rooms.end())
        return std::nullopt;
    T* free_room = dynamic_cast<T*>(it -> get());
    return Stay("", *free_room, main_guest, start, end);
}

#endif
