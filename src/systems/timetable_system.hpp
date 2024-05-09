#include <vector>
#include <ranges>
#include <algorithm>
#include "../types/timetable_entry.hpp"
#include "../workers/worker.hpp"
#include "worker_system.hpp"

#ifndef TIMETABLE_SYSTEM_HPP
#define TIMETABLE_SYSTEM_HPP

class TimetableSystem
{
    public:
        TimetableSystem() = default;
        TimetableSystem(const TimetableSystem&) = delete;
        TimetableSystem(TimetableSystem&&) = delete;
        TimetableSystem& operator=(const TimetableSystem&) = delete;
        TimetableSystem& operator=(TimetableSystem&&) = delete;
        
        WorkerSystem& get_worker_system() const;
        void bind_worker_system(WorkerSystem&); 
        void add_entry(const TimetableEntry&);
        void remove_entry(const TimetableEntry&);

        const std::vector<TimetableEntry>& get_entries() const noexcept;
        std::vector<const TimetableEntry*> worker_entries(const Worker&) const noexcept;
        
        static const jed_utils::timespan minimal_break;
    private:
        std::vector<TimetableEntry> entries;
        WorkerSystem* worker_system = nullptr;
};

#endif
