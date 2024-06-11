#include "inner_task.hpp"


InnerTask::InnerTask(const Task& task) : Task{task} {}

WeakOwnSystemObserver<Worker>& InnerTask::get_wosow() { return *this; }
WeakMultipleOwnSystemObserver<Worker>& InnerTask::get_wmosow() { return *this; }
WeakOwnSystemObserver<Room>& InnerTask::get_wosor() { return *this; }
WeakOwnSystemObserver<Guest>& InnerTask::get_wosog() { return *this; }
const WeakOwnSystemObserver<Worker>& InnerTask::get_wosow() const noexcept { return *this; }
const WeakMultipleOwnSystemObserver<Worker>& InnerTask::get_wmosow() const noexcept { return *this; }
const WeakOwnSystemObserver<Room>& InnerTask::get_wosor() const noexcept { return *this; }
const WeakOwnSystemObserver<Guest>& InnerTask::get_wosog() const noexcept { return *this; }
