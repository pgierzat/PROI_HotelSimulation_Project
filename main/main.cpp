#include "../src/hotel_io/hotel_io.hpp"
#include "../src/simulation/simulator.hpp"
#include <fstream>
#include <memory>
#include <iostream>


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <workers.json> <rooms.json>\n";
        return 1;
    }

    auto workers = HotelIO::read_workers(argv[1]);
    auto rooms = HotelIO::read_rooms(argv[2]);

    auto init_time = jed_utils::datetime{2024, 6, 6};

    HotelSystem hotel_system{init_time};
    auto& w_system = hotel_system.get_w_system();
    for (const auto& worker : workers)
        w_system.add_worker(*worker);
    auto& rooms_list = hotel_system.get_rooms_list();
    for (const auto& room : rooms )
        rooms_list.add_room(*room);

    Simulator simulator(hotel_system);
    simulator.simulate();

    return 0;
}
