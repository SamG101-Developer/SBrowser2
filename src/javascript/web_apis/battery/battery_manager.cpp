#include "battery_manager.hpp"
#include "battery_manager_private.hpp"

#include "battery/detail/algorithm_internals.hpp"


battery::battery_manager::battery_manager()
{
    INIT_PIMPL(battery_manager);
}


auto battery::battery_manager::get_charging() const -> ext::boolean
{
    ACCESS_PIMPL(const battery_manager);
    return d->charging();
}


auto battery::battery_manager::get_charging_time() const -> ext::number<double>
{
    ACCESS_PIMPL(const battery_manager);
    return d->charging_time();
}


auto battery::battery_manager::get_discharging_time() const -> ext::number<double>
{
    ACCESS_PIMPL(const battery_manager);
    return d->discharging_time();
}


auto battery::battery_manager::get_level() const -> ext::number<double>
{
    ACCESS_PIMPL(const battery_manager);
    return d->level();
}


auto battery::battery_manager::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<battery_manager>{isolate}
        .inherit<dom::nodes::event_target>()
        .property("charging", &battery_manager::get_charging)
        .property("chargingTime", &battery_manager::get_charging_time)
        .property("dischargingTime", &battery_manager::get_discharging_time)
        .property("level", &battery_manager::get_level)
        .auto_wrap_objects();

    return std::move(conversion);
}
