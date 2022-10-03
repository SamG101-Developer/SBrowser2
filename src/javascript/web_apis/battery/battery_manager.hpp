#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP

#include "dom/nodes/event_target.hpp"
namespace battery {class battery_manager;}
namespace battery {class battery_manager_private;}


class battery::battery_manager
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(battery_manager);
    MAKE_PIMPL(battery_manager);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(charging, ext::boolean);
    DEFINE_GETTER(charging_time, ext::number<double>);
    DEFINE_GETTER(discharging_time, ext::number<double>);
    DEFINE_GETTER(level, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_BATTERY_MANAGER_HPP
