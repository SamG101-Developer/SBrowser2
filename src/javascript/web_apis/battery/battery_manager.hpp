#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP

#include "dom/nodes/event_target.hpp"
namespace battery {class battery_manager;}

#include USE_INNER_TYPES(battery)


class battery::battery_manager
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(battery_manager);
    battery_manager();

public js_properties:
    ext::property<ext::boolean> charging;
    ext::property<ext::number<double>> charging_time;
    ext::property<ext::number<double>> discharging_time;
    ext::property<ext::number<double>> level;

public cpp_members:
    MAKE_PIMPL(battery_manager);
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(charging);
    DEFINE_CUSTOM_GETTER(charging_time);
    DEFINE_CUSTOM_GETTER(discharging_time);
    DEFINE_CUSTOM_GETTER(level);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP
