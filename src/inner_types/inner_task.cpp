#include "inner_task.hpp"


InnerTask::InnerTask(const Task& task) : Task{task} {}

WOSOw& InnerTask::get_wosow() { return *this; }
WMOSOw& InnerTask::get_wmosow() { return *this; }
WOSOr& InnerTask::get_wosor() { return *this; }
WOSOg& InnerTask::get_wosog() { return *this; }
const WOSOw& InnerTask::get_wosow() const noexcept { return *this; }
const WMOSOw& InnerTask::get_wmosow() const noexcept { return *this; }
const WOSOr& InnerTask::get_wosor() const noexcept { return *this; }
const WOSOg& InnerTask::get_wosog() const noexcept { return *this; }