#ifndef JSON_ROOM_HPP
#define JSON_ROOM_HPP

#include <memory>
#include "../utilities/errors.hpp"
#include "../utilities/json.hpp"
#include "../utilities/errors.hpp"
#include "../utilities/concepts.hpp"
#include "../rooms/hpp/one_room.hpp"
#include "../rooms/hpp/two_room.hpp"
#include "../rooms/hpp/three_room.hpp"
#include "../rooms/hpp/four_room.hpp"
#include "../rooms/hpp/two_appartment.hpp"
#include "../rooms/hpp/four_appartment.hpp"

class JSONRoom
{
    using json = nlohmann::json;
    public:
        static json write(const Room&);
        template<SupportedRoom T>
            static T read_specific(const json&);
        static std::unique_ptr<Room> read(const json&);
    private:
        template<SupportedRoom T>
            static T unchecked_read_specific(const json&);
        static RoomType get_type(const json&);
};


template<SupportedRoom T>
T JSONRoom::read_specific(const json& j)
{
    RoomType type = get_type(j);
    if (T::type != type)
        throw IncorrectRoomType(
            "Room parsed from JSON has another type than expected",
            T::type, type
        );
    return unchecked_read_specific<T>(j);
}


template<SupportedRoom T>
T JSONRoom::unchecked_read_specific(const json& j)
{
    try
    {
        std::string number = j.at("id");
        return T{number};
    } catch(const json::exception& e) {
        throw JSONException("Error parsing Room", j);
    } catch(const std::invalid_argument& e) {
        throw JSONInvalidData("Error parsing Room", j);
    }
}

#endif
