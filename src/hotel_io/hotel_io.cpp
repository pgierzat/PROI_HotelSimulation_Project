#include "hotel_io.hpp"
#include "../fileio/JSON_file.hpp"
#include "../JSON_converters/JSON_room.hpp"
#include "../JSON_converters/JSON_worker.hpp"


std::vector<std::unique_ptr<Room>> HotelIO::read_rooms(const Path& path)
{
    auto file = JSONFile{path};
    auto j = file.read();
    auto rooms = std::vector<std::unique_ptr<Room>>{};
    for (const auto& room_data : j)
    {
        auto room = JSONRoom::read(room_data);
        rooms.push_back(std::move(room));
    }
    return rooms;
}

std::vector<std::unique_ptr<Worker>> HotelIO::read_workers(const Path& path)
{
    auto file = JSONFile{path};
    auto j = file.read();
    auto workers = std::vector<std::unique_ptr<Worker>>{};
    for (const auto& worker_data : j)
    {
        auto worker = JSONWorker::read(worker_data);
        workers.push_back(std::move(worker));
    }
    return workers;
}

void HotelIO::write_rooms(const Path& path, const std::vector<const Room*>& rooms)
{
    auto j = nlohmann::json{};
    for (const auto& room : rooms)
    {
        auto room_data = JSONRoom::write(*room);
        j.push_back(room_data);
    }
    auto file = JSONFile{path};
    file.write(j);
}

void HotelIO::write_workers(const Path& path, const std::vector<const Worker*>& workers)
{
    auto j = nlohmann::json{};
    for (const auto& worker : workers)
    {
        auto room_data = JSONWorker::write(*worker);
        j.push_back(room_data);
    }
    auto file = JSONFile{path};
    file.write(j);
}
