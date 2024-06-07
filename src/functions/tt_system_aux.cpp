#include "tt_system_aux.hpp"
#include <ranges>
#include <algorithm>


SameWorkerID::SameWorkerID(const Worker& worker) : worker{worker} {}

bool SameWorkerID::operator()(const TimetableEntry& entry) { return entry.get_worker() == worker; }

bool SameWorkerID::operator()(const std::unique_ptr<TimetableEntry>& entry) {
    return entry -> get_worker() == worker;
}

ShiftInInterval::ShiftInInterval(const Worker& worker, const TimeInterval& interval) :
    same_worker{worker}, interval{interval} {}

bool ShiftInInterval::operator()(const TimetableEntry& entry)
{
    return same_worker(entry) && is_in(entry.get_start(), interval);
}

bool ShiftInInterval::operator()(const std::unique_ptr<TimetableEntry>& entry)
{
    return same_worker(entry) && is_in(entry -> get_start(), interval);
}

TooShortBreak::TooShortBreak(const TimeInterval& interval, jed_utils::timespan minimal_break) :
    interval{interval}, minimal_break{minimal_break} {}

bool TooShortBreak::operator()(const TimetableEntry& entry)
{
    return distance( interval, entry.get_interval() ) < minimal_break;
}

bool TooShortBreak::operator()(const std::unique_ptr<TimetableEntry>& entry)
{
    return distance( interval, entry -> get_interval() ) < minimal_break;
}

std::vector<const TimetableEntry*> interval_entries(const std::vector<const TimetableEntry*>& entries,
    const TimeInterval& interval)
{
    std::vector<const TimetableEntry*> output;
    for (auto entry : entries)
    {
        if (is_in(entry -> get_date(), interval))
            output.push_back(entry);
    }
    return output;
}

std::vector<const TimetableEntry*> month_entries(const std::vector<const TimetableEntry*>& entries,
    std::chrono::year_month month)
{
    return interval_entries(entries, TimeInterval::month_to_interval(month));
}

std::vector<const TimetableEntry*> worker_entries(const std::vector<const TimetableEntry*>& entries,
    const Worker& worker)
{
    std::vector<const TimetableEntry*> vec;
    for (auto entry : entries | std::views::filter(
            [&](auto otr_entry){ return otr_entry -> get_worker() == worker; }))
        vec.push_back(entry);
    return vec;
}

unsigned hours_worked(const std::vector<const TimetableEntry*>& entries, const Worker& worker,
    std::chrono::year_month month)
{
    auto shift_duration = static_cast<unsigned>( worker.get_shift_duration().get_hours() );
    auto pred = ShiftInInterval(worker, TimeInterval::month_to_interval(month));
    unsigned shifts_worked = std::ranges::count_if(entries, pred, [](auto entry){ return *entry; });
    return shifts_worked * shift_duration;
}
