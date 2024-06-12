#ifndef T_SYSTEM_AUX_HPP
#define T_SYSTEM_AUX_HPP

#include <string>
#include <memory>
#include "../inner_types/inner_task.hpp"


class TaskSameWorker
{
    public:
        TaskSameWorker(const std::string& id);
        bool operator()(const InnerTask&) const noexcept;
    private:
        std::string id;
};


class TaskSameRoom
{
    public:
        TaskSameRoom(const std::string& id);
        bool operator()(const InnerTask&) const noexcept;
    private:
        std::string id;
};


class TaskSameGuest
{
    public:
        TaskSameGuest(const std::string& id);
        bool operator()(const InnerTask&) const noexcept;
    private:
        std::string id;
};


#endif
