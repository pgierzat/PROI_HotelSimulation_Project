#include <vector>
#include <ranges>
#include <algorithm>
#include "../types/timetable_entry.hpp"
#include "../utilities/useful.hpp"
#include "../workers/worker.hpp"
#include "worker_system.hpp"

#ifndef TIMETABLE_SYSTEM_HPP
#define TIMETABLE_SYSTEM_HPP

class TimetableSystem
{
    public:
        TimetableSystem() = default;
        
        void bind_worker_system(WorkerSystem&); 
        const WorkerSystem& get_worker_system() const;
        void set_time(const jed_utils::datetime&);
        void add_entry(const TimetableEntry&);
        void remove_entry(const TimetableEntry&);
        const std::vector<TimetableEntry>& get_entries() const noexcept;
        std::vector<TimetableEntry*> get_active_entries() const noexcept;
        std::vector<TimetableEntry*> get_ending_entries() const noexcept;
        std::vector<const TimetableEntry*> worker_entries(const Worker&) const noexcept;
        static const jed_utils::timespan minimal_break;
    private:
        void refresh_active_entries();
        void refresh_ending_entries(const std::vector<TimetableEntry*> previous_entries);
        std::vector<TimetableEntry> entries;
        std::vector<TimetableEntry*> active_entries;
        std::vector<TimetableEntry*> ending_entries;
        WorkerSystem* worker_system = nullptr;
        jed_utils::datetime time{1970, 1, 1};
};

std::vector<const TimetableEntry*> interval_entries(const std::vector<const TimetableEntry*>&,
    const TimeInterval&);
std::vector<const TimetableEntry*> month_entries(const std::vector<const TimetableEntry*>&,
    std::chrono::year_month);

#endif
