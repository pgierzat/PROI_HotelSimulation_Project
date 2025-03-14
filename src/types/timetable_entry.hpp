#include "../workers/worker.hpp"
#include "../auxiliary/own_system_observer.hpp"
#include "time_interval.hpp"
#include "datetime.h"
#include <chrono>

#ifndef TIMETABLE_ENTRY
#define TIMETABLE_ENTRY

class WorkerSystem;
class TimetableSystem;

class TimetableEntry : protected OwnSystemObserver<Worker>
{
    public:
        TimetableEntry(const std::string& id, const Worker&, const jed_utils::datetime&, Shift);
        TimetableEntry(const std::string& id, const jed_utils::datetime&, Shift);
        const Worker& get_worker() const;
        const std::string& get_id() const noexcept;
        jed_utils::datetime get_date() const noexcept;
        jed_utils::datetime get_start() const;
        jed_utils::datetime get_end() const;
        TimeInterval get_interval() const;
        Shift get_shift() const noexcept;
        void set_worker(const Worker&);
        void set_shift(Shift);
        void set_date(const jed_utils::datetime&);
        bool operator==(const TimetableEntry&) const;
    private:
        static void check_worker_shift(const Worker&, Shift);
        std::string id;
        jed_utils::datetime date;
        Shift shift;
};

std::ostream& operator<<(std::ostream&, const TimetableEntry&);

#endif
