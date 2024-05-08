#ifndef ROOM_NOT_FOUND_EXCEPTION_HPP
#define ROOM_NOT_FOUND_EXCEPTION_HPP

#include <stdexcept>

class RoomNotFoundException : public std::invalid_argument
{
    public:
        RoomNotFoundException();
};


#endif