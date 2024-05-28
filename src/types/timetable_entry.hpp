#include "../workers/worker.hpp"
#include "time_interval.hpp"
#include "datetime.h"
#include <chrono>

#ifndef TIMETABLE_ENTRY
#define TIMETABLE_ENTRY

class WorkerSystem;

class TimetableEntry
{
    public:
        TimetableEntry(const Worker&, const jed_utils::datetime&, Shift);
        const Worker& get_worker() const;
        jed_utils::datetime get_date() const noexcept;
        jed_utils::datetime get_start() const;
        jed_utils::datetime get_end() const;
        TimeInterval get_interval() const;
        Shift get_shift() const noexcept;
        void set_worker(const Worker&);
        void set_shift(Shift);
        void set_date(const jed_utils::datetime&);
        bool operator==(const TimetableEntry&) const;
        static void set_w_system(const WorkerSystem&) noexcept;
    private:
        static const WorkerSystem* w_system;
        static void check_worker_shift(const Worker&, Shift);
        std::string worker_id;
        jed_utils::datetime date;
        Shift shift;
};

std::ostream& operator<<(std::ostream&, const TimetableEntry&);

#endif
