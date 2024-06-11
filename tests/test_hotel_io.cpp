#include "catch_amalgamated.hpp"
#include "../src/hotel_io/hotel_io.hpp"
#include "../src/workers/cook.hpp"
#include "../src/workers/maid.hpp"
#include "../src/workers/receptionist.hpp"
#include "../src/workers/waiter.hpp"
#include "../src/rooms/hpp/two_room.hpp"
#include "../src/rooms/hpp/four_appartment.hpp"

TEST_CASE("Test HotelIO")
{
    SECTION("Test write/read workers")
    {
        auto pay = Pay{PaycheckMethod::Salary, Amount{3200, 0}};
        auto worker1 = Receptionist{"id1", "name1", pay};
        auto worker2 = Waiter{"id2", "name2", pay};
        auto workers = std::vector<const Worker*>{&worker1, &worker2};
        auto path = std::filesystem::path{"../test_files/workers.json"};
        HotelIO::write_workers(path, workers);
        auto read_workers = HotelIO::read_workers(path);
        REQUIRE(std::ranges::equal(workers, read_workers, [](auto p1, const auto& p2){ return *p1 == *p2; }));
    }

    SECTION("Test write/read workers")
    {
        auto room1 = FourAppartment{"237"};
        auto room2 = TwoRoom{"238"};
        auto rooms = std::vector<const Room*>{&room1, &room2};
        auto path = std::filesystem::path{"../test_files/rooms.json"};
        HotelIO::write_rooms(path, rooms);
        auto read_rooms = HotelIO::read_rooms(path);
        REQUIRE(std::ranges::equal(rooms, read_rooms, [](auto p1, const auto& p2){ return *p1 == *p2; }));
    }
}