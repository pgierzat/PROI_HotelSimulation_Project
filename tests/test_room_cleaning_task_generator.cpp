#include "catch_amalgamated.hpp"
#include "../src/simulation/room_cleaning_task_generator.hpp"
#include "../src/systems/hotel_system.hpp"
#include "../src/systems/guest_system.hpp"
#include "../src/systems/worker_system.hpp"
#include "../src/rooms/hpp/rooms_list.hpp"
#include "../src/rooms/hpp/one_room.hpp"
#include "../src/rooms/hpp/two_appartment.hpp"
#include "../src/tasks/room_cleaning_task.hpp"


TEST_CASE("Test RoomCleaningTaskGenerator")
{
    auto h_system = HotelSystem{};
    jed_utils::datetime time0{2024, 5, 19};
    h_system.get_ck().set_time(time0);
    auto& rooms_list = h_system.get_rooms_list();
    rooms_list.add_room(TwoAppartment{"237"});
    rooms_list.add_room(OneRoom{"238"});
    const auto& room1 = rooms_list.get_by_id("237");
    const auto& room2 = rooms_list.get_by_id("238");
    auto& t_system = h_system.get_t_system();
    auto gen = RoomCleaningTaskGenerator{h_system};

    SECTION("time test")
    {
        jed_utils::datetime time1{2024, 5, 19, 7};
        gen.set_time(time1);
        REQUIRE(t_system.get_tasks().empty());
        jed_utils::datetime time2{2024, 5, 19, 8};
        gen.set_time(time2);
        auto task1 = RoomCleaningTask{"1", room1};
        auto task2 = RoomCleaningTask{"2", room2};
        auto expected = std::vector{task1, task2};
        auto tasks = t_system.get_tasks();
        REQUIRE(std::ranges::equal(tasks, expected, [](auto t1, const auto& t2){ return *t1 == t2; }));
    }
}
