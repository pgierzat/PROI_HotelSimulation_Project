#include "stay_generator.hpp"
#include "../systems/hotel_system.hpp"
#include "../types/guest.hpp"
#include "../auxiliary/id_generator.hpp"
#include "../rooms/hpp/one_room.hpp"
#include "../rooms/hpp/two_room.hpp"
#include "../rooms/hpp/three_room.hpp"
#include "../rooms/hpp/four_room.hpp"
#include <random>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>


StayGenerator::StayGenerator(HotelSystem& h_system) :
    RandomGenerator{h_system.get_ck(), 0.1, timespan{0, 1}},
    rooms_list{&h_system.get_crooms_list()},
    s_system{&h_system.get_s_system()},
    g_system{&h_system.get_g_system()} {}

void StayGenerator::generate()
{
    
    const int guests_nr = guests_interval(normal_guests(engine));
    const int days = 1 + days_interval(uniform_days(engine));
    auto guests = generate_guests(guests_nr);
    auto stay_opt = std::optional<Stay>{};
    if (guests_nr == 1)
        stay_opt = generate_stay<OneRoom>(guests, days);
    else if (guests_nr == 2)
        stay_opt = generate_stay<TwoRoom>(guests, days);
    else if (guests_nr == 3)
        stay_opt = generate_stay<ThreeRoom>(guests, days);
    else if (guests_nr == 4)
        stay_opt = generate_stay<FourRoom>(guests, days);
    auto msg = std::string{};
    if (not stay_opt)
        msg = std::to_string(guests_nr) +
            " guests came to the hotel, but there was no available room for them.";
    else {
        auto& stay = stay_opt.value();
        std::ranges::for_each(guests, [&](const auto& guest){ g_system -> add_guest(guest); });
        for (const auto& guest : guests | std::views::drop(1))
            stay.add_guest(guest);
        s_system -> add_stay_id(stay);
        msg = std::to_string(guests_nr) +
            " guests came to the hotel, they booked stay ending at " +
            stay.get_end().to_string();
    }
    std::ofstream file("output.txt", std::ios::app);
    if (file.is_open()) {
        file << time.to_string() << ": " << msg << '\n';
    }
}

std::vector<Guest> StayGenerator::generate_guests(unsigned guests_nr)
{
    std::vector<Guest> guests{};
    for (int i = guests_nr; i != 0 ; i--) {
        auto nr = g_system -> get_free_id();
        Guest guest = Guest(nr, "name" + nr);
        guests.push_back(guest);
    }
    return guests;
}
