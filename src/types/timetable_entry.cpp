#include "timetable_entry.hpp"
#include <stdexcept>

TimetableEntry::TimetableEntry(const Worker& worker, const jed_utils::datetime& date, Shift shift) : 
    worker{&worker}, date{date}, shift{shift}
{
    (this -> date).trunkate();
    check_worker_shift(*(this -> worker), shift);
}

const Worker& TimetableEntry::get_worker() const noexcept { return *worker; }

jed_utils::datetime TimetableEntry::get_date() const noexcept { return date; }

TimeInterval TimetableEntry::get_interval() const noexcept
{
    jed_utils::timespan start_delta = worker -> get_shift_start(shift);
    jed_utils::datetime start_dt = date + start_delta;
    jed_utils::timespan duration = worker -> get_shift_duration();
    return TimeInterval{start_dt, start_dt + duration};
}

Shift TimetableEntry::get_shift() const noexcept { return shift; }

void TimetableEntry::set_worker(const Worker& worker)
{
    check_worker_shift(worker, shift);
    this -> worker = &worker;
}

void TimetableEntry::set_shift(Shift shift)
{
    check_worker_shift(*worker, shift);
    this -> shift = shift;
}

void TimetableEntry::set_date(const jed_utils::datetime& date)
{
    this -> date = date;
    (this -> date).trunkate();
}

bool TimetableEntry::operator==(const TimetableEntry& other) const
{
    return *worker == other.get_worker() &&
        date == other.get_date() &&
        shift == other.get_shift();
}

void TimetableEntry::check_worker_shift(const Worker& worker, Shift shift)
{
    if (worker.get_shifts() < unsigned(shift))
        throw std::invalid_argument("There is no such shift for these workers.");
}

SameWorker::SameWorker(const Worker& worker) : worker{worker} {}

bool SameWorker::operator()(const TimetableEntry& entry) { return entry.get_worker() == worker; }

std::ostream& operator<<(std::ostream& os, const TimetableEntry& entry)
{
    return os << entry.get_date().to_string("yyyy-MM-dd") << ' ' << entry.get_shift() << ' '
        << entry.get_worker().get_id();
}
