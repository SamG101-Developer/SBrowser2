#include "battery_manager.hpp"


battery::battery_manager::battery_manager()
        : s_charging{true}
        , s_charging_time{0.0}
        , s_discharging_time{ext::number<double>::inf()}
        , s_level{1.0}
{}


auto battery::battery_manager::get_charging()
        const -> decltype(this->charging)::value_t
{
    // The charging getter steps are to return this.[[Charging]].
    return s_charging();
}


auto battery::battery_manager::get_charging_time()
        const -> decltype(this->charging_time)::value_t
{
    // The chargingTime getter steps are to return this.[[ChargingTime]].
    return s_charging_time();
}


auto battery::battery_manager::get_discharging_time()
        const -> decltype(this->discharging_time)::value_t
{
    // The dischargingTime getter steps are to return this.[[DischargingTime]].
    return s_discharging_time();
}


auto battery::battery_manager::get_level()
        const -> decltype(this->level)::value_t
{
    // The level getter steps are to return this.[[Level]].
    return s_level();
}


auto battery::battery_manager::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<battery_manager>{isolate}
        .inherit<dom::nodes::event_target>()
        .var("charging", &battery_manager::charging, true)
        .var("chargingTime", &battery_manager::charging_time, true)
        .var("dischargingTime", &battery_manager::discharging_time, true)
        .var("level", &battery_manager::level, true)
        .auto_wrap_objects();
}
