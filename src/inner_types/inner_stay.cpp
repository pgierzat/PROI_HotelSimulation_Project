#include "inner_stay.hpp"
#include <algorithm>


InnerStay::InnerStay(const Stay& stay) :
    Stay{id, stay.get_room(), stay.get_main_guest(), stay.get_start(), stay.get_end()} {}

OwnSystemObserver<Room>& InnerStay::get_room_observer() noexcept { return *this; }

MultipleOwnSystemObserver<Guest>& InnerStay::get_guests_observer() noexcept { return *this; }

const MultipleOwnSystemObserver<Guest>& InnerStay::get_cguests_observer() const noexcept { return *this; }

const OwnSystemObserver<Room>& InnerStay::get_croom_observer() const noexcept { return *this; }
