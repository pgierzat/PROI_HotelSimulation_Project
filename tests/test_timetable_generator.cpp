#include "catch_amalgamated.hpp"
#include "../src/simulation/timetable_generator.hpp"
#include "../src/systems/hotel_system.hpp"


TEST_CASE("Test TimetableGenerator")
{
    auto h_system = HotelSystem{};
    auto& w_system = h_system.get_w_system();
    auto pay = Pay{PaycheckMethod::Salary, Amount{3200, 0}};
    auto worker1 = Waiter{"id1", "name1",  pay};
    auto worker2 = Waiter{"id2", "name2",  pay};
    auto worker3 = Waiter{"id3", "name3",  pay};
    auto worker4 = Maid{"id4", "name4",  pay};
    auto worker5 = Maid{"id5", "name5",  pay};
    auto worker6 = Maid{"id6", "name6",  pay};
    auto worker7 = Maid{"id7", "name7",  pay};
    auto worker8 = Maid{"id8", "name8",  pay};
    auto worker9 = Maid{"id9", "name9",  pay};
    auto worker10 = Cook{"id10", "name10",  pay};
    auto worker11 = Cook{"id11", "name11",  pay};
    auto worker12 = Receptionist{"id12", "name12",  pay};
    auto worker13 = Receptionist{"id13", "name13",  pay};
    auto worker14 = Receptionist{"id14", "name14",  pay};
    w_system.add_worker(worker1);
    w_system.add_worker(worker2);
    w_system.add_worker(worker3);
    w_system.add_worker(worker4);
    w_system.add_worker(worker5);
    w_system.add_worker(worker6);
    w_system.add_worker(worker7);
    w_system.add_worker(worker8);
    w_system.add_worker(worker9);
    w_system.add_worker(worker10);
    w_system.add_worker(worker11);
    w_system.add_worker(worker12);
    w_system.add_worker(worker13);
    w_system.add_worker(worker14);
    auto& tt_system = h_system.get_tt_system();
    auto time0 = jed_utils::datetime{2024, 6, 1};    // saturday
    h_system.set_time(time0);
    auto gen = TimetableGenerator{h_system};
    REQUIRE(tt_system.get_entries().empty());

    SECTION("time test")
    {
        auto time1 = jed_utils::datetime{2024, 6, 1, 22};   // still saturday
        gen.set_time(time1);
        REQUIRE(tt_system.get_entries().empty());
        auto time2 = jed_utils::datetime{2024, 6, 9, 4};    // sunday
        gen.set_time(time2);
        auto cook_entries = 7 * worker10.get_workers_per_shift() * worker10.get_shifts();
        auto maid_entries = 7 * worker8.get_workers_per_shift() * worker8.get_shifts();
        auto receptionist_entries = 7 * worker14.get_workers_per_shift() * worker14.get_shifts();
        auto waiter_entries = 7 * worker1.get_workers_per_shift() * worker1.get_shifts();
        REQUIRE( tt_system.get_entries().size() == cook_entries + maid_entries +
            receptionist_entries + waiter_entries  );
    }
}