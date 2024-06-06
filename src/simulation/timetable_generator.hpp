#ifndef TIMETABLE_GENERATOR_HPP
#define TIMETABLE_GENERATOR_HPP

#include "generator.hpp"
#include "../systems/timetable_system.hpp"
#include "../types/timetable_entry.hpp"
#include "../systems/worker_system.hpp"
#include "../types/datetime.h"
#include "../utilities/concepts.hpp"
#include "../functions/min_map_item.hpp"
#include <chrono>
#include <utility>

class TimetableGenerator : public Generator
{
    using TTE = TimetableEntry;
    public:
        TimetableGenerator(HotelSystem&);
    private:
        void generate() override;
        void initiate_time_next();
        template<SupportedWorker T>
            std::vector<TTE> generate_empty_entries(const jed_utils::datetime& monday);
        template<SupportedWorker T>
            std::vector<TTE>& assign_entries(std::vector<TTE>&);
        void set_time_next() noexcept override;
        TimetableSystem* tt_system;
        const WorkerSystem* w_system;
};

template<SupportedWorker T>
std::vector<TimetableEntry> TimetableGenerator::generate_empty_entries(const jed_utils::datetime& monday)
{
    auto temp = T{};
    unsigned shifts = temp.get_shifts();
    unsigned w_per_shift = temp.get_workers_per_shift();
    auto next_monday = monday;
    next_monday.add_days(7);
    auto entries = std::vector<TTE>{};
    for (auto current = monday; current != next_monday; current.add_days(1))
        for (unsigned i = 1; i <= shifts; ++i)
        {
            auto shift = static_cast<Shift>(i);
            for (unsigned j = 0; j < w_per_shift; ++j)
                entries.push_back(TTE{current, shift});
        }
    return entries;
}

template<SupportedWorker T>
std::vector<TimetableEntry>& TimetableGenerator::assign_entries(std::vector<TTE>& entries)
{
    auto worker_shifts = std::vector<std::pair<const T*, unsigned>>{};
    auto workers = w_system -> get_specific_workers<T>();
    if (workers.empty() && not entries.empty())
        throw EntryAssignmentError("There is no Worker to assign an entry to", entries[0]);
    std::ranges::for_each(workers, [&](auto worker){ worker_shifts.emplace_back(worker, 0); });
    for (auto& entry : entries)
    {
        auto pos = worker_shifts.begin();
        do {
            nth_map_item(worker_shifts, pos);
            auto suggested_worker =  pos -> first;
            entry.set_worker(*suggested_worker);
            ++pos;
        } while (not tt_system -> check_minimal_break(entry) && pos != worker_shifts.end());
        if (pos == worker_shifts.end() && not tt_system -> check_minimal_break(entry))
            throw EntryAssignmentError("There is no Worker to assign this entry to.", entry);
        tt_system -> add_entry(entry);
        ++ pos -> second;
    }
    return entries;
}

#endif
