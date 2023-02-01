#pragma once
#ifndef SBROWSER2_INPUT_EVENT_HPP
#define SBROWSER2_INPUT_EVENT_HPP

#include "ui_events/ui_event.hpp"
namespace ui_events {class input_event;}

#include <memory>
#include "ext/vector.hpp"
namespace dom::node_ranges {class static_range;}
namespace html::dnd {class data_transfer;}


class ui_events::input_event
        : public ui_event
{
public constructors:
    DOM_CTORS(input_event);
    input_event() = default;
    input_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

private js_methods:
    /* INPUT_EVENTS */
    auto get_target_ranges() -> ext::vector<dom::node_ranges::static_range*>*;

private js_properties:
    /* UI_EVENTS */
    ext::property<ext::string> data;
    ext::property<ext::string> input_type;
    ext::property<ext::boolean> is_composing;

    /* INPUT_EVENTS */
    ext::property<std::unique_ptr<html::dnd::data_transfer>> data_transfer;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    std::unique_ptr<ext::vector<dom::node_ranges::static_range*>> m_static_ranges;
};


#endif //SBROWSER2_INPUT_EVENT_HPP
