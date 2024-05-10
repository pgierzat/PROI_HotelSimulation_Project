#include "stay_system.hpp"
#include <ranges>
#include <algorithm>

const jed_utils::timespan StaySystem::minimal_break = jed_utils::timespan{1, 0, 0, 0};

void StaySystem::bind_guest_system(const GuestSystem& g_system)
{
    this -> g_system = &g_system;
}

void StaySystem::bind_room_system(const RoomsList& rooms_list)
{
    this -> rooms_list = &rooms_list;
}

void StaySystem::add_stay(const Stay& stay)
{
    const auto& room = stay.get_room();
    auto interval = stay.get_interval();
    auto room_stays = std::ranges::filter_view(stays,
        [&](const auto & otr_stay){ return otr_stay.get_room() == room; });
    auto p = std::ranges::find_if(room_stays,
        [&](const auto& otr_stay){ return distance( interval, otr_stay.get_interval() ) < minimal_break; });
    if ( p != room_stays.end() )
        throw std::invalid_argument("This worker must have an 11-hour's break between shifts.");
    stays.push_back(stay);
}

void StaySystem::remove_stay(const Stay& stay) { std::erase(stays, stay); }

std::vector<Stay> StaySystem::get_stays() const noexcept { return stays; }
