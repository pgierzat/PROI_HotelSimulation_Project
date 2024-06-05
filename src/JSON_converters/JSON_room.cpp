#include "JSON_room.hpp"


nlohmann::json JSONRoom::write(const Room& room)
{
    return {
        {"id", room.get_id()},
        {"type", Room::rtype_to_str(room.get_type())}
    };
}

std::unique_ptr<Room> JSONRoom::read(const json& j)
{
    try
    {
        RoomType type = get_type(j);
        switch (type)
        {
            case RoomType::OneRoom:
                return std::make_unique<OneRoom>(unchecked_read_specific<OneRoom>(j));
            case RoomType::TwoRoom:
                return std::make_unique<TwoRoom>(unchecked_read_specific<TwoRoom>(j));
            case RoomType::ThreeRoom:
                return std::make_unique<ThreeRoom>(unchecked_read_specific<ThreeRoom>(j));
            case RoomType::FourRoom:
                return std::make_unique<FourRoom>(unchecked_read_specific<FourRoom>(j));
            case RoomType::TwoAppartment:
                return std::make_unique<TwoAppartment>(unchecked_read_specific<TwoAppartment>(j));
            case RoomType::FourAppartment:
                return std::make_unique<FourAppartment>(unchecked_read_specific<FourAppartment>(j));
            default:
                throw UnsupportedRoomTypeError{"Tried to parse a room of unknown type from json.", type};
        }
    } catch(const json::exception& e) {
        throw JSONException("Error parsing Room", j);
    } catch(const std::invalid_argument& e) {
        throw JSONInvalidData("Error parsing Room", j);
    }
}

RoomType JSONRoom::get_type(const json& j)
{
    auto type_str = std::string{};
    try {
        type_str = j.at("type");
    } catch(const json::exception& e) {
        throw JSONException("Error parsing Room's type", j);
    }
    return Room::str_to_rtype(type_str);
}
