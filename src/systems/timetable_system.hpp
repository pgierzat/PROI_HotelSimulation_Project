#include <vector>
#include <ranges>
#include <algorithm>
#include "../types/timetable_entry.hpp"
#include "../utilities/useful.hpp"
#include "../workers/worker.hpp"
#include "worker_system.hpp"

#ifndef TIMETABLE_SYSTEM_HPP
#define TIMETABLE_SYSTEM_HPP

enum class EntryStatus {
    scheduled,
    in_progress,
    finished
};

class TimetableSystem
{
    public:
        TimetableSystem(WorkerSystem&);
        const WorkerSystem& get_cw_system() const noexcept;
        const jed_utils::datetime& get_time() const noexcept;
        void set_time(const jed_utils::datetime&);
        void add_entry(const TimetableEntry&);
        void remove_entry(const TimetableEntry&);
        const std::vector<TimetableEntry>& get_entries() const noexcept;
        EntryStatus get_entry_status(const TimetableEntry&) const noexcept;
        std::vector<const Worker*> workers_available() const noexcept;
        static const jed_utils::timespan minimal_break;
    private:
        std::vector<TimetableEntry> entries;
        WorkerSystem* w_system = nullptr;
        jed_utils::datetime time{1970, 1, 1};
};

#endif
