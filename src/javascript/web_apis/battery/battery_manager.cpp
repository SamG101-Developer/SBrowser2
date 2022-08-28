#include "battery_manager.hpp"


battery::battery_manager::battery_manager()
        : s_charging{true}
        , s_charging_time{0.0}
        , s_discharging_time{ext::number<double>::inf()}
        , s_level{1.0}
{}


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
