#ifndef INNER_STAY_HPP
#define INNER_STAY_HPP

#include "../types/stay.hpp"
#include "../auxiliary/own_system_observer.hpp"
#include <vector>


class InnerStay : public Stay
{
    public:
        InnerStay(const Stay&);
        MultipleOwnSystemObserver<Guest>& get_guests_observer() noexcept;
        OwnSystemObserver<Room>& get_room_observer() noexcept;
        const MultipleOwnSystemObserver<Guest>& get_cguests_observer() const noexcept;
        const OwnSystemObserver<Room>& get_croom_observer() const noexcept;
};


#endif
