#include "timetable_system.hpp"
#include "../functions/has_elem.hpp"
#include "../functions/tt_system_aux.hpp"
#include "../types/datetime.h"
#include "../types/timespan.h"


const jed_utils::timespan TimetableSystem::minimal_break = jed_utils::timespan{0, 11, 0, 0};;

TimetableSystem::TimetableSystem(WorkerSystem& w_system) : w_system{&w_system}
{
    TimetableEntry::set_w_system(w_system);
}

const WorkerSystem& TimetableSystem::get_cw_system() const noexcept { return *w_system; }

const jed_utils::datetime& TimetableSystem::get_time() const noexcept { return time; }

void TimetableSystem::set_time(const jed_utils::datetime& time)
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
    entries.push_back(entry);
}

void TimetableSystem::remove_entry(const TimetableEntry& entry) { std::erase(entries, entry); }

const std::vector<TimetableEntry>& TimetableSystem::get_entries() const noexcept { return entries; }

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
    auto active_entries_lambda = [&](const auto& entry){ return is_in(time, entry.get_interval()); };
    for (const TimetableEntry& entry : entries | std::views::filter(active_entries_lambda))
        w_available.push_back(&entry.get_worker());
    return w_available;
}

bool TimetableSystem::check_minimal_break(const TimetableEntry& entry)
{
    auto worker_entries = std::ranges::filter_view(entries, SameWorker(entry.get_worker()));
    auto p = std::ranges::find_if(worker_entries, TooShortBreak{entry.get_interval(), minimal_break});
    return p == worker_entries.end();
}
