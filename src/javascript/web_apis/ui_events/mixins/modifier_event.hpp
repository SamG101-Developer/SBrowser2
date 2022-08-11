#pragma once
#ifndef SBROWSER2_MODIFIER_EVENT_HPP
#define SBROWSER2_MODIFIER_EVENT_HPP

#include "ui_events/ui_event.hpp"
namespace ui_events::mixins {class modifier_event;}

class ui_events::mixins::modifier_event
        : public ui_event
{
public constructors:
    modifier_event() = default;
    modifier_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_methods:
    auto get_modifier_state(ext::string_view arg) -> ext::boolean;

public js_properties:
    ext::property<ext::boolean> ctrl_key;
    ext::property<ext::boolean> shift_key;
    ext::property<ext::boolean> alt_key;
    ext::property<ext::boolean> meta_key;

    ext::property<ext::boolean> modifier_alt_graph;
    ext::property<ext::boolean> modifier_caps_lock;
    ext::property<ext::boolean> modifier_fn;
    ext::property<ext::boolean> modifier_fn_lock;
    ext::property<ext::boolean> modifier_hyper;
    ext::property<ext::boolean> modifier_num_lock;
    ext::property<ext::boolean> modifier_scroll_lock;
    ext::property<ext::boolean> modifier_symbol;
    ext::property<ext::boolean> modifier_symbol_lock;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_MODIFIER_EVENT_HPP
