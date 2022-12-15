module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.battery.battery_manager;
import apis.dom.event_target;

import ext.boolean;
import ext.enums;
import ext.number;
import ext.tuple;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(battery, battery_manager)
        : virtual public dom::event_target
{
public constructors:
    DOM_CTORS(battery_manager);
    MAKE_PIMPL(battery_manager);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(charging, ext::boolean);
    DEFINE_GETTER(charging_time, ext::number<double>);
    DEFINE_GETTER(discharging_time, ext::number<double>);
    DEFINE_GETTER(level, ext::number<double>);
};

