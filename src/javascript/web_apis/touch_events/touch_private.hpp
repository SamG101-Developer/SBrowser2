#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include "ext/memory.ixx"

#include INCLUDE_INNER_TYPES(touch_events)
namespace dom::nodes {class event_target;}


DEFINE_PRIVATE_CLASS(touch_events, touch) : virtual dom_object_private
{
    ext::number<long> identifier;
    std::observer_ptr<dom::nodes::event_target> target;
    ext::number<double> screen_x;
    ext::number<double> screen_y;
    ext::number<double> client_x;
    ext::number<double> client_y;
    ext::number<double> page_x;
    ext::number<double> page_y;
    ext::number<float> radius_x;
    ext::number<float> radius_y;
    ext::number<float> rotation_angle;
    ext::number<float> force;
    ext::number<float> altitude_angle;
    ext::number<float> azimuth_angle;
    detail::touch_type_t touch_type;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_PRIVATE_HPP
