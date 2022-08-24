#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP

#include "dom/nodes/event_target.hpp"
namespace battery {class battery_manager;}


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

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private js_slots:
    ext::slot<ext::boolean> s_charging;
    ext::slot<ext::number<double>> s_charging_time;
    ext::slot<ext::number<double>> s_discharging_time;
    ext::slot<ext::number<double>> s_level;

private cpp_accessors:
    DEFINE_GETTER(charging);
    DEFINE_GETTER(charging_time);
    DEFINE_GETTER(discharging_time);
    DEFINE_GETTER(level);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP
