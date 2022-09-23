#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_EVENT_PRIVATE_HPP

#include "dom/events/event_private.hpp"

#include "ext/pimpl.hpp"
namespace dom::other {class dom_exception;}


DEFINE_PRIVATE_CLASS(sensors, sensor_event) : dom::events::event_private
{
    std::unique_ptr<dom::other::dom_exception> error;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SENSORS_SENSOR_EVENT_PRIVATE_HPP
