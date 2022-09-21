#include "battery_manager.hpp"

#include "battery/detail/algorithm_internals.hpp"


battery::battery_manager::battery_manager()
        : INIT_PIMPL
{}


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
