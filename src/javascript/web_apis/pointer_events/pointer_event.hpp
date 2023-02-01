#pragma once
#ifndef SBROWSER2_POINTER_EVENT_HPP
#define SBROWSER2_POINTER_EVENT_HPP

#include "ui_events/mouse_event.hpp"
namespace pointer_events {class pointer_event;}
namespace pointer_events {class pointer_event_private;}

#include "ext/span.hpp"


class pointer_events::pointer_event
        : public ui_events::mouse_event
{
public constructors:
    pointer_event() = default;
    pointer_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(pointer_event);
    MAKE_V8_AVAILABLE;

private js_methods:
    _EXT_NODISCARD auto get_coalesced_events() const -> ext::vector_span<pointer_event*>;
    _EXT_NODISCARD auto get_predicted_events() const -> ext::vector_span<pointer_event*>;

private js_properties:
    DEFINE_GETTER(pointer_id, ext::number<long>);
    DEFINE_GETTER(width, ext::number<double>);
    DEFINE_GETTER(height, ext::number<double>);
    DEFINE_GETTER(pressure, ext::number<float>);
    DEFINE_GETTER(tangential_pressure, ext::number<float>);
    DEFINE_GETTER(tilt_x, ext::number<long>);
    DEFINE_GETTER(tilt_y, ext::number<long>);
    DEFINE_GETTER(twist, ext::number<long>);
    DEFINE_GETTER(altitude_angle, ext::number<double>);
    DEFINE_GETTER(azimuth_angle, ext::number<double>);
    DEFINE_GETTER(pointer_type, ext::string_view);
    DEFINE_GETTER(is_primary, ext::boolean);

    DEFINE_SETTER(target, dom::nodes::event_target*);
};


#endif //SBROWSER2_POINTER_EVENT_HPP
