#include "room_not_found_exception.hpp"

RoomNotFoundException::RoomNotFoundException() :
std::invalid_argument("Room not found") {}