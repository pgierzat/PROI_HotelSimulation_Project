#ifndef STAY_GENERATOR_HPP
#define STAY_GENERATOR_HPP


#include "../rooms/hpp/rooms_list.hpp"
#include "../systems/stay_system.hpp"
#include "generator.hpp"

// create rand * guest
// move them to matching room
// create stay
// add stay to stay_system

class StayGenerator : public Generator
{
    const RoomsList* rooms_list;
    StaySystem* s_system;
    public:
        StayGenerator(StaySystem&, const RoomsList&, const jed_utils::datetime&);
    private:
        void generate() override;
        void set_time_next() noexcept override;
        void initiate_time_next();
};
#endif