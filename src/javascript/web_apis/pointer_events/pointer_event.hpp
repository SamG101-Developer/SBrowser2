#pragma once
#ifndef SBROWSER2_POINTER_EVENT_HPP
#define SBROWSER2_POINTER_EVENT_HPP

#include "ui_events/mouse_event.hpp"
namespace pointer_events {class pointer_event;}


class pointer_events::pointer_event
        : public ui_events::mouse_event
{
public constructors:
    DOM_CTORS(pointer_event);
    pointer_event() = default;
    pointer_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_methods:
    auto get_coalesced_events() const -> ext::vector<pointer_event*>*;
    auto get_predicted_events() const -> ext::vector<pointer_event*>*;

public js_properties:
    ext::property<ext::number<long>> pointer_id;
    ext::property<ext::number<double>> width;
    ext::property<ext::number<double>> height;
    ext::property<ext::number<float>> pressure;
    ext::property<ext::number<float>> tangential_pressure;
    ext::property<ext::number<long>> tilt_x;
    ext::property<ext::number<long>> tilt_y;
    ext::property<ext::number<long>> twist;
    ext::property<ext::number<double>> altitude_angle;
    ext::property<ext::number<double>> azimuth_angle;
    ext::property<ext::number<ext::string>> pointer_type;
    ext::property<ext::number<ext::boolean>> is_primary;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    std::unique_ptr<ext::vector<pointer_event*>> m_coalesced_events;
    std::unique_ptr<ext::vector<pointer_event*>> m_predicted_events;

private cpp_accessors:
    auto set_target(dom::nodes::event_target* val) -> void;
};


#endif //SBROWSER2_POINTER_EVENT_HPP
