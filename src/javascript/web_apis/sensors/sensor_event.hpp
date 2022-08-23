#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_EVENT_HPP

#include "dom/events/event.hpp"
namespace sensors {class sensor_event;}

namespace dom::other {class dom_exception;}

class sensors::sensor_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(sensor_event);
    sensor_event() = default;
    sensor_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<std::unique_ptr<dom::other::dom_exception>> error;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_EVENT_HPP