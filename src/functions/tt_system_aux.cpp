#include "tt_system_aux.hpp"
#include <ranges>


SameWorker::SameWorker(const Worker& worker) : worker{worker} {}

bool SameWorker::operator()(const TimetableEntry& entry) { return entry.get_worker() == worker; }

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
