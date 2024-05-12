#include "timetable_system.hpp"
#include "/opt/datetime.h"
#include "/opt/timespan.h"


const jed_utils::timespan TimetableSystem::minimal_break = jed_utils::timespan{0, 11, 0, 0};;

void TimetableSystem::bind_worker_system(WorkerSystem& worker_system)
{
    this -> worker_system = &worker_system;
}

void TimetableSystem::set_time(const jed_utils::datetime& time)
{
    if (time < this -> time)
        throw std::invalid_argument("Tried to turn TimetableSystem's time back.");
    this -> time = time;
    auto previous_entries = active_entries;
    refresh_active_entries();
    refresh_ending_entries(previous_entries);
}

const WorkerSystem& TimetableSystem::get_worker_system() const { return *worker_system; }

void TimetableSystem::add_entry(const TimetableEntry& entry)
{
    const auto& worker = entry.get_worker();
    const auto& interval = entry.get_interval();
    auto worker_entries = std::ranges::filter_view(entries, SameWorker(worker));
    auto p = std::ranges::find_if(worker_entries,
        [&](const auto& otr_entry){ return distance( interval, otr_entry.get_interval() ) < minimal_break; });
    if ( p != worker_entries.end() )
        throw std::invalid_argument("This worker must have an 11-hour's break between shifts.");
    entries.push_back(entry);
}

void TimetableSystem::remove_entry(const TimetableEntry& entry) { std::erase(entries, entry); }

const std::vector<TimetableEntry>& TimetableSystem::get_entries() const noexcept { return entries; }
std::vector<TimetableEntry*> TimetableSystem::get_active_entries() const noexcept { return active_entries; }
std::vector<TimetableEntry*> TimetableSystem::get_ending_entries() const noexcept { return ending_entries; }

std::vector<const TimetableEntry*> TimetableSystem::worker_entries(const Worker& worker) const noexcept
{
    std::vector<const TimetableEntry*> vec;
    for (const auto& entry : entries | std::views::filter(SameWorker(worker)))
        vec.push_back(&entry);
    return vec;
}

void TimetableSystem::refresh_active_entries()
{
    active_entries.clear();
    for (auto& entry : entries)
    {
        if (is_in(time, entry.get_interval()))
            active_entries.push_back(&entry);
    }
    std::ranges::sort(active_entries);
}

void TimetableSystem::refresh_ending_entries(const std::vector<TimetableEntry*> previous_entries)
{
    ending_entries.clear();
    std::ranges::set_difference(previous_entries, active_entries, std::back_inserter(ending_entries));
}
