#include "timetable_entry.hpp"
#include "../systems/worker_system.hpp"
#include <stdexcept>

const WorkerSystem* TimetableEntry::w_system = nullptr;

TimetableEntry::TimetableEntry(const Worker& worker, const jed_utils::datetime& date, Shift shift) : 
    worker_id{worker.get_id()}, date{date}, shift{shift}
{
    (this -> date).trunkate();
    check_worker_shift(worker, shift);
}

const Worker& TimetableEntry::get_worker() const
{
    return w_system -> get_by_id(worker_id);
}

jed_utils::datetime TimetableEntry::get_date() const noexcept { return date; }

jed_utils::datetime TimetableEntry::get_start() const
{
    return date + get_worker().get_shift_start(shift);
}

jed_utils::datetime TimetableEntry::get_end() const
{
    const auto& worker = get_worker();
    return date + worker.get_shift_start(shift) + worker.get_shift_duration();
}

TimeInterval TimetableEntry::get_interval() const
{
    return TimeInterval{get_start(), get_end()};
}

Shift TimetableEntry::get_shift() const noexcept { return shift; }

void TimetableEntry::set_worker(const Worker& worker)
{
    check_worker_shift(worker, shift);
    this -> worker_id = worker.get_id();
}

void TimetableEntry::set_shift(Shift shift)
{
    const auto& worker = get_worker();
    check_worker_shift(worker, shift);
    this -> worker_id = worker.get_id();
}

void TimetableEntry::set_date(const jed_utils::datetime& date)
{
    this -> date = date;
    (this -> date).trunkate();
}

bool TimetableEntry::operator==(const TimetableEntry& other) const
{
    return worker_id == other.worker_id &&
        date == other.date &&
        shift == other.shift;
}

void TimetableEntry::check_worker_shift(const Worker& worker, Shift shift)
{
    if (worker.get_shifts() < unsigned(shift))
        throw std::invalid_argument("There is no such shift for these workers.");
}

void TimetableEntry::set_w_system(const WorkerSystem& w_system) noexcept
{
    TimetableEntry::w_system = &w_system;
}

std::ostream& operator<<(std::ostream& os, const TimetableEntry& entry)
{
    return os << entry.get_date().to_string("yyyy-MM-dd") << ' ' <<
        Worker::shift_to_str(entry.get_shift()) << ' ' <<
        entry.get_worker().get_id();
}
