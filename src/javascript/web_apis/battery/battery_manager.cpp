#include "battery_manager.hpp"
#include "battery_manager_private.hpp"

#include "battery/detail/algorithm_internals.hpp"


battery::battery_manager::battery_manager()
{
    INIT_PIMPL(battery_manager);
}


auto battery::battery_manager::get_charging() const -> ext::boolean
{
    // The 'charging' getter returns the equivalent 'charging' attribute value that is stored in the private class.
    // Method call becuase the value is always changing, and has to be got at the exact time the property is accessed.
    ACCESS_PIMPL(const battery_manager);
    return d->charging();
}


auto battery::battery_manager::get_charging_time() const -> ext::number<double>
{
    // The 'charging_time' getter returns the equivalent 'charging_time' attribute value that is stored in the private
    // class. Method call becuase the value is always changing, and has to be got at the exact time the property is
    // accessed.
    ACCESS_PIMPL(const battery_manager);
    return d->charging_time();
}


auto battery::battery_manager::get_discharging_time() const -> ext::number<double>
{
    // The 'discharging_time' getter returns the equivalent 'discharging_time' attribute value that is stored in the
    // private class. Method call becuase the value is always changing, and has to be got at the exact time the property
    // is accessed.
    ACCESS_PIMPL(const battery_manager);
    return d->discharging_time();
}


auto battery::battery_manager::get_level() const -> ext::number<double>
{
    // The 'level' getter returns the equivalent 'level' attribute value that is stored in the private class. Method
    // call becuase the value is always changing, and has to be got at the exact time the property is accessed.
    ACCESS_PIMPL(const battery_manager);
    return d->level();
}


auto battery::battery_manager::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::nodes::event_target>()
        .property("charging", &battery_manager::get_charging)
        .property("chargingTime", &battery_manager::get_charging_time)
        .property("dischargingTime", &battery_manager::get_discharging_time)
        .property("level", &battery_manager::get_level)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}
