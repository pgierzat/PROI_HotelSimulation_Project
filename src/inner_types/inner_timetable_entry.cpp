#include "inner_timetable_entry.hpp"


InnerTimetableEntry::InnerTimetableEntry(const TimetableEntry& entry) :
    TimetableEntry{entry} {}
OwnSystemObserver<Worker>& InnerTimetableEntry::get_worker_observer() noexcept {
    return *this;
}

const OwnSystemObserver<Worker>& InnerTimetableEntry::get_cworker_observer() const noexcept {
    return *this;
}
