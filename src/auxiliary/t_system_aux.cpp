#include "t_system_aux.hpp"

TaskSameWorker::TaskSameWorker(const std::string& id) : id{id} {}

bool TaskSameWorker::operator()(const InnerTask& task) const noexcept
{
    auto& wosow = task.get_wosow();
    if (wosow.get_observed_id() == id)
        return true;
    auto& wmosow = task.get_wmosow();
    for (auto pid : wmosow.get_observed_ids())
        if (*pid == id)
            return true;
    return false;
}

TaskSameRoom::TaskSameRoom(const std::string& id) : id{id} {}

bool TaskSameRoom::operator()(const InnerTask& task) const noexcept {
    auto& wosor = task.get_wosor();
    return wosor.get_observed_id() == id;
}

TaskSameGuest::TaskSameGuest(const std::string& id) : id{id} {}

bool TaskSameGuest::operator()(const InnerTask& task) const noexcept {
    auto& wosog = task.get_wosog();
    return wosog.get_observed_id() == id;
}
