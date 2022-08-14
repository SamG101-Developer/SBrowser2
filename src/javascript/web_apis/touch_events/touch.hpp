#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_HPP

#include "dom_object.hpp"
namespace touch_events {class touch;}

#include "touch_events/_typedef.hpp"
namespace dom::nodes {class event_target;}

class touch_events::touch
        : public virtual dom_object
{
public constructors:
    touch(ext::map<ext::string, ext::any>&& options);

public js_properties:
    ext::property<ext::number<long>> identifier;
    ext::property<ext::number<dom::nodes::event_target*>> target;
    ext::property<ext::number<double>> screen_x;
    ext::property<ext::number<double>> screen_y;
    ext::property<ext::number<double>> client_x;
    ext::property<ext::number<double>> client_y;
    ext::property<ext::number<double>> page_x;
    ext::property<ext::number<double>> page_y;
    ext::property<ext::number<float>> radius_x;
    ext::property<ext::number<float>> radius_y;
    ext::property<ext::number<float>> rotation_angle;
    ext::property<ext::number<float>> force;
    ext::property<ext::number<float>> altitude_angle;
    ext::property<ext::number<float>> azimuth_angle;
    ext::property<ext::number<detail::touch_type_t>> touch_type;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_HPP
