#include "timetable_system.hpp"
#include <algorithm>
#include "../functions/has_elem.hpp"
#include "../functions/vec_to_pvec.hpp"
#include "../functions/tt_system_aux.hpp"
#include "../types/datetime.h"
#include "../types/timespan.h"
#include "../types/timetable_entry.hpp"
#include "../workers/worker.hpp"
#include "worker_system.hpp"


const jed_utils::timespan TimetableSystem::minimal_break = jed_utils::timespan{0, 11, 0, 0};;

TimetableSystem::TimetableSystem(WorkerSystem& w_system) : w_system{&w_system}
{
    TimetableEntry::set_w_system(w_system);
}

const jed_utils::datetime& TimetableSystem::get_time() const noexcept { return time; }

void TimetableSystem::notify(const jed_utils::datetime& time)
{
    if (time < this -> time)
        throw TurnBackTimeError("Tried to turn TimetableSystem's time back.", time);
    this -> time = time;
}

void TimetableSystem::add_entry(const TimetableEntry& entry)
{
    if (entry.get_start() < time)
        throw EntryScheduleError("Tried to add a TimetableEntry that has already started.", entry);
    if (not check_minimal_break(entry))
        throw MinimalBreakError("This worker must have an 11-hour's break between shifts.", entry);
    entries.push_back(std::make_unique<TimetableEntry>(entry));
}

void TimetableSystem::remove_entry(const TimetableEntry& entry) { std::erase(entries, entry); }

std::optional<const TimetableEntry*> TimetableSystem::find_by_id(const std::string& id) const
{
    auto p = std::ranges::find_if(entries, [&](const auto& entry){ return entry -> get_id() == id; });
    if (p == entries.end())
        return std::nullopt;
    return &**p;
}

const TimetableEntry& TimetableSystem::get_by_id(const std::string& id) const
{
    auto p = std::ranges::find_if(entries, [&](const auto& entry){ return entry -> get_id() == id; });
    if (p == entries.end())
        throw EntryNotInSystemError("TimetableSystem::get_by_id() failed", id);
    return **p;
}

std::vector<const TimetableEntry*> TimetableSystem::get_entries() const noexcept { return vec_to_pvec(entries); }

EntryStatus TimetableSystem::get_entry_status(const TimetableEntry& entry) const noexcept
{
    if (time < entry.get_start())
        return EntryStatus::scheduled;
    if (time <= entry.get_end())
        return EntryStatus::in_progress;
    return EntryStatus::finished;
}

std::vector<const Worker*> TimetableSystem::workers_available() const noexcept
{
    std::vector<const Worker*> w_available;
    auto active_entries_lambda = [&](const auto& entry){ return is_in(time, entry -> get_interval()); };
    for (const auto& entry : entries | std::views::filter(active_entries_lambda))
        w_available.push_back(&entry -> get_worker());
    return w_available;
}

bool TimetableSystem::check_minimal_break(const TimetableEntry& entry)
{
    auto worker_entries = std::ranges::filter_view(entries, SameWorker(entry.get_worker()));
    auto p = std::ranges::find_if(worker_entries, TooShortBreak{entry.get_interval(), minimal_break});
    return p == worker_entries.end();
}
