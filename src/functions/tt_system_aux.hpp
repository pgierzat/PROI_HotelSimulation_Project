#ifndef TT_SYSTEM_AUX_HPP
#define TT_SYSTEM_AUX_HPP

#include "../inner_types/inner_timetable_entry.hpp"
#include "../types/time_interval.hpp"
#include <vector>


class SameWorkerID
{
    public:
        SameWorkerID(const Worker&);
        bool operator()(const TimetableEntry&);
        bool operator()(const std::unique_ptr<InnerTimetableEntry>&);
    private:
        const Worker& worker;
};

class ShiftInInterval
{
    public:
        ShiftInInterval(const Worker&, const TimeInterval&);
        bool operator()(const TimetableEntry&);
        bool operator()(const std::unique_ptr<InnerTimetableEntry>&);
    private:
        SameWorkerID same_worker;
        TimeInterval interval;
};

class TooShortBreak
{
    public:
        TooShortBreak(const TimeInterval&, jed_utils::timespan minimal_break);
        bool operator()(const TimetableEntry&);
        bool operator()(const std::unique_ptr<InnerTimetableEntry>&);
    private:
        TimeInterval interval;
        jed_utils::timespan minimal_break;
};

std::vector<const TimetableEntry*> interval_entries(const std::vector<const TimetableEntry*>&,
    const TimeInterval&);
std::vector<const TimetableEntry*> month_entries(const std::vector<const TimetableEntry*>&,
    std::chrono::year_month);
std::vector<const TimetableEntry*> worker_entries(const std::vector<const TimetableEntry*>&,
    const Worker&);
std::vector<const TimetableEntry*> active_entries(const std::vector<const TimetableEntry*>&,
    const jed_utils::datetime&);
unsigned hours_worked(const std::vector<const TimetableEntry*>&, const Worker&, std::chrono::year_month);

#endif
