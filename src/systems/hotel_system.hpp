#ifndef HOTEL_SYSTEM_HPP
#define HOTEL_SYSTEM_HPP

#include "clock.hpp"
#include "../rooms/hpp/rooms_list.hpp"
#include "guest_system.hpp"
#include "paycheck_system.hpp"
#include "service_system.hpp"
#include "stay_system.hpp"
#include "task_system.hpp"
#include "timetable_system.hpp"
#include "worker_system.hpp"

class HotelSystem
{
    public:
        HotelSystem();
        HotelSystem(const HotelSystem&) = delete;
        const Clock& get_ck() const noexcept;
        const jed_utils::datetime& get_time() const noexcept;
        const GuestSystem& get_cg_system() const noexcept;
        const WorkerSystem& get_cw_system() const noexcept;
        const RoomsList& get_crooms_list() const noexcept;
        const StaySystem& get_cs_system() const noexcept;
        const TimetableSystem& get_ctt_system() const noexcept;
        const PaycheckSystem& get_cpc_system() const noexcept;
        const TaskSystem& get_ct_system() const noexcept;
        const ServiceSystem& get_csc_system() const noexcept;
        GuestSystem& get_g_system() noexcept;
        WorkerSystem& get_w_system() noexcept;
        RoomsList& get_rooms_list() noexcept;
        StaySystem& get_s_system() noexcept;
        TimetableSystem& get_tt_system() noexcept;
        PaycheckSystem& get_pc_system() noexcept;
        TaskSystem& get_t_system() noexcept;
        ServiceSystem& get_sc_system() noexcept;
    private:
        Clock ck;
        GuestSystem g_system;
        WorkerSystem w_system;
        RoomsList rooms_list;
        StaySystem s_system;
        TimetableSystem tt_system;
        PaycheckSystem pc_system;
        TaskSystem t_system;
        ServiceSystem sc_system;
};


#endif
