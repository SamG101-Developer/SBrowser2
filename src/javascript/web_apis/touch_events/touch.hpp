#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_HPP


namespace touch_events {class touch;}
namespace touch_events {class touch_private;}

#include INCLUDE_INNER_TYPES(touch_events)
namespace dom::nodes {class event_target;}

class touch_events::touch
        : public virtual dom_object
{
public constructors:
    touch(detail::touch_init&& options);
    MAKE_PIMPL(touch);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(identifier, ext::number<long>);
    DEFINE_GETTER(target, dom::nodes::event_target*);
    DEFINE_GETTER(screen_x, ext::number<double>);
    DEFINE_GETTER(screen_y, ext::number<double>);
    DEFINE_GETTER(client_x, ext::number<double>);
    DEFINE_GETTER(client_y, ext::number<double>);
    DEFINE_GETTER(page_x, ext::number<double>);
    DEFINE_GETTER(page_y, ext::number<double>);
    DEFINE_GETTER(radius_x, ext::number<float>);
    DEFINE_GETTER(radius_y, ext::number<float>);
    DEFINE_GETTER(rotation_angle, ext::number<float>);
    DEFINE_GETTER(force, ext::number<float>);
    DEFINE_GETTER(altitude_angle, ext::number<float>);
    DEFINE_GETTER(azimuth_angle, ext::number<float>);
    DEFINE_GETTER(touch_type, detail::touch_type_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_TOUCH_EVENTS_TOUCH_HPP
