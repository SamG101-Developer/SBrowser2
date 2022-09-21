#include "battery_manager.hpp"

#include "battery/detail/algorithm_internals.hpp"


battery::battery_manager::battery_manager()
        : INIT_PIMPL
{}


auto battery::battery_manager::get_charging() const -> typename decltype(this->charging)::value_t
{return d_ptr->charging;}


auto battery::battery_manager::get_charging_time() const -> typename decltype(this->charging_time)::value_t
{return d_ptr->charging_time;}


auto battery::battery_manager::get_discharging_time() const -> typename decltype(this->discharging_time)::value_t
{return d_ptr->discharging_time;}


auto battery::battery_manager::get_level() const -> typename decltype(this->level)::value_t
{return d_ptr->level;}


auto battery::battery_manager::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<battery_manager>{isolate}
        .inherit<dom::nodes::event_target>()
        .var("charging", &battery_manager::charging, true)
        .var("chargingTime", &battery_manager::charging_time, true)
        .var("dischargingTime", &battery_manager::discharging_time, true)
        .var("level", &battery_manager::level, true)
        .auto_wrap_objects();

    return std::move(conversion);
}
