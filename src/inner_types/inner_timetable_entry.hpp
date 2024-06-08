#ifndef INNER_TIMETABLE_ENTRY_HPP
#define INNER_TIMETABLE_ENTRY_HPP

#include "../types/timetable_entry.hpp"

class InnerTimetableEntry : public TimetableEntry
{
    public:
        InnerTimetableEntry(const TimetableEntry&);
        OwnSystemObserver<Worker>& get_worker_observer() noexcept;
        const OwnSystemObserver<Worker>& get_cworker_observer() const noexcept;
};


#endif
