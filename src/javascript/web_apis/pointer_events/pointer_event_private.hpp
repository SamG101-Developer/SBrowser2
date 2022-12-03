#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_POINTER_EVENTS_POINTER_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_POINTER_EVENTS_POINTER_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "ui_events/mouse_event_private.hpp"

#include "ext/boolean.ixx"
#include "ext/number.ixx"
#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace pointer_events {class pointer_event;}


DEFINE_PRIVATE_CLASS(pointer_events, pointer_event) : ui_events::mouse_event_private
{
    ext::number<long> pointer_id;
    ext::number<double> width;
    ext::number<double> height;
    ext::number<float> pressure;
    ext::number<float> tangential_pressure;
    ext::number<long> tilt_x;
    ext::number<long> tilt_y;
    ext::number<long> twist;
    ext::number<double> altitude_angle;
    ext::number<double> azimuth_angle;
    ext::string pointer_type;
    ext::boolean is_primary;

    ext::vector<pointer_event*> coalesced_events;
    ext::vector<pointer_event*> predicted_events;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_POINTER_EVENTS_POINTER_EVENT_PRIVATE_HPP
