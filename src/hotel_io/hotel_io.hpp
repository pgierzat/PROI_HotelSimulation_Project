#ifndef HOTEL_IO_HPP
#define HOTEL_IO_HPP

#include <vector>
#include <memory>
#include <filesystem>
#include <string>
#include "../JSON_converters/JSON_room.hpp"

class HotelIO
{
    public:
        using Path = std::filesystem::path;
        static std::vector<std::unique_ptr<Room>> read_rooms(const Path& path);
        static std::vector<std::unique_ptr<Worker>> read_workers(const Path& path);
        static void write_rooms(const Path& path, const std::vector<const Room*>& rooms);
        static void write_workers(const Path& path, const std::vector<const Worker*>& workers);
};


#endif
