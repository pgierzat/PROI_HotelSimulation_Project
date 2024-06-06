#include "hotel_system.hpp"


HotelSystem::HotelSystem() :
    ck{}, g_system{}, w_system{}, rooms_list{}, s_system{g_system, rooms_list},
    tt_system{w_system}, pc_system{w_system, tt_system},
    t_system{w_system, rooms_list, g_system},
    sc_system{g_system, w_system, rooms_list, s_system, t_system} {}

const Clock& HotelSystem::get_ck() const noexcept { return ck; }
const jed_utils::datetime& HotelSystem::get_time() const noexcept { return ck.get_time(); }
const GuestSystem& HotelSystem::get_cg_system() const noexcept { return g_system; }
const WorkerSystem& HotelSystem::get_cw_system() const noexcept { return w_system; }
const RoomsList& HotelSystem::get_crooms_list() const noexcept { return rooms_list; }
const StaySystem& HotelSystem::get_cs_system() const noexcept { return s_system; }
const TimetableSystem& HotelSystem::get_ctt_system() const noexcept { return tt_system; }
const PaycheckSystem& HotelSystem::get_cpc_system() const noexcept { return pc_system; }
const TaskSystem& HotelSystem::get_ct_system() const noexcept { return t_system; }
const ServiceSystem& HotelSystem::get_csc_system() const noexcept { return sc_system; }

GuestSystem& HotelSystem::get_g_system() noexcept { return g_system; }
WorkerSystem& HotelSystem::get_w_system() noexcept { return w_system; }
RoomsList& HotelSystem::get_rooms_list() noexcept { return rooms_list; }
StaySystem& HotelSystem::get_s_system() noexcept { return s_system; }
TimetableSystem& HotelSystem::get_tt_system() noexcept { return tt_system; }
PaycheckSystem& HotelSystem::get_pc_system() noexcept { return pc_system; }
TaskSystem& HotelSystem::get_t_system() noexcept { return t_system; }
ServiceSystem& HotelSystem::get_sc_system() noexcept { return sc_system; }
