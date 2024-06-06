#include <vector>
#include <memory>
#include "../auxiliary/time_observer.hpp"
#include "../utilities/useful.hpp"
#include "../types/timetable_entry.hpp"

#ifndef TIMETABLE_SYSTEM_HPP
#define TIMETABLE_SYSTEM_HPP

class TimetableEntry;
class WorkerSystem;

enum class EntryStatus {
    scheduled,
    in_progress,
    finished
};

class TimetableSystem : public TimeObserver
{
    public:
        TimetableSystem(WorkerSystem&);
        TimetableSystem(const TimetableSystem&) = delete;
        const jed_utils::datetime& get_time() const noexcept;
        void notify(const jed_utils::datetime&) override;
        void add_entry(const TimetableEntry&);
        void remove_entry(const TimetableEntry&);
        std::optional<const TimetableEntry*> find_by_id(const std::string&) const;
        const TimetableEntry& get_by_id(const std::string&) const;
        std::vector<const TimetableEntry*> get_entries() const noexcept;
        EntryStatus get_entry_status(const TimetableEntry&) const noexcept;
        std::vector<const Worker*> workers_available() const noexcept;
        bool check_minimal_break(const TimetableEntry&);
        static const jed_utils::timespan minimal_break;
    private:
        std::vector<std::unique_ptr<TimetableEntry>> entries;
        WorkerSystem* w_system = nullptr;
        jed_utils::datetime time{1970, 1, 1};
};

#endif
