#include "timetable_entry.hpp"
#include "../systems/worker_system.hpp"
#include <stdexcept>

TimetableEntry::TimetableEntry(const std::string& id, const Worker& worker, const jed_utils::datetime& date, Shift shift) : 
    OwnSystemObserver<Worker>{worker}, id{id}, date{date}, shift{shift}
{
    (this -> date).trunkate();
    check_worker_shift(worker, shift);
}

TimetableEntry::TimetableEntry(const std::string& id, const jed_utils::datetime& date, Shift shift) :
    OwnSystemObserver<Worker>{}, id{id}, date{date}, shift{shift}
{
    (this -> date).trunkate();
}

const Worker& TimetableEntry::get_worker() const { return OwnSystemObserver<Worker>::get(); }

const std::string& TimetableEntry::get_id() const noexcept { return id;}

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
    OwnSystemObserver<Worker>::set(worker);
}

void TimetableEntry::set_shift(Shift shift)
{
    const auto& worker = get_worker();
    check_worker_shift(worker, shift);
}

void TimetableEntry::set_date(const jed_utils::datetime& date)
{
    this -> date = date;
    (this -> date).trunkate();
}

bool TimetableEntry::operator==(const TimetableEntry& other) const
{
    return get_worker() == other.get_worker() &&
        date == other.date &&
        shift == other.shift;
}

void TimetableEntry::check_worker_shift(const Worker& worker, Shift shift)
{
    if (worker.get_shifts() < unsigned(shift))
        throw std::invalid_argument("There is no such shift for these workers.");
}

std::ostream& operator<<(std::ostream& os, const TimetableEntry& entry)
{
    return os << entry.get_date().to_string("yyyy-MM-dd") << ' ' <<
        Worker::shift_to_str(entry.get_shift()) << ' ' <<
        entry.get_worker().get_id();
}
