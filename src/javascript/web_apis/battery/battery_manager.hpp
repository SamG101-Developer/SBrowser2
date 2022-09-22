#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP

#include "dom/nodes/event_target.hpp"
namespace battery {class battery_manager;}

#include "battery/battery_manager_private.hpp"


class battery::battery_manager
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(battery_manager);
    battery_manager();

    MAKE_PIMPL(battery_manager);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(charging, ext::boolean) {return d_ptr->charging;}
    DEFINE_GETTER(charging_time, ext::number<double>) {return d_ptr->charging_time;}
    DEFINE_GETTER(discharging_time, ext::number<double>) {return d_ptr->discharging_time;}
    DEFINE_GETTER(level, ext::number<double>) {return d_ptr->level;}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP
