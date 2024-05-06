#include "workers/worker.hpp"
#include "time_interval.hpp"
#include "/opt/datetime.h"
#include <chrono>

#ifndef TIMETABLE_ENTRY
#define TIMETABLE_ENTRY


class TimetableEntry
{
    public:
        TimetableEntry(const Worker&, const jed_utils::datetime&, Shift);
        TimetableEntry(const Worker&);
        TimetableEntry(const jed_utils::datetime&, Shift);
        TimetableEntry(const jed_utils::datetime&);
        TimetableEntry() = default;
        const Worker& get_worker() const noexcept;
        jed_utils::datetime get_date() const noexcept;
        TimeInterval get_interval() const noexcept;
        Shift get_shift() const noexcept;

        void set_worker(const Worker&);
        void set_shift(Shift);
        void set_date(const jed_utils::datetime&);
        bool operator==(const TimetableEntry&) const;
    private:
        static void check_worker_shift(const Worker*, Shift);

        const Worker* worker = nullptr;
        jed_utils::datetime date;
        Shift shift;
};

std::ostream& operator<<(std::ostream&, const TimetableEntry&);

class SameWorker
{
    public:
        SameWorker(const Worker&);
        bool operator()(const TimetableEntry&);
    private:
        const Worker& worker;
};

#endif
