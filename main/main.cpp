#include "../src/hotel_io/hotel_io.hpp"
#include "../src/simulation/simulator.hpp"
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <workers.json> <rooms.json>\n";
        return 1;
    }

    HotelIO hotel_io;
    auto workers = hotel_io.read_workers(argv[1]);
    // moving vector to list
    std::vector<std::unique_ptr<Room>> rooms_vector = hotel_io.read_rooms(argv[2]);
    std::list<std::unique_ptr<Room>> rooms;
    std::move(rooms_vector.begin(), rooms_vector.end(), std::back_inserter(rooms));
    rooms_vector.clear();

    WorkerSystem worker_system(std::move(workers));
    RoomsList rooms_list(std::move(rooms));
    HotelSystem hotel_system;  // Assuming HotelSystem has a default constructor

    Simulator simulator(hotel_system, worker_system, rooms_list);
    simulator.simulate();

    return 0;
}

