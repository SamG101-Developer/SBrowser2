#pragma once
#ifndef SBROWSER2_MODIFIER_EVENT_HPP
#define SBROWSER2_MODIFIER_EVENT_HPP

#include "ui_events/ui_event.hpp"
namespace ui_events::mixins {class modifier_event;}
namespace ui_events::mixins {class modifier_event_private;}


class ui_events::mixins::modifier_event
        : public ui_event
{
public constructors:
    modifier_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(modifier_event);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto get_modifier_state(ext::string_view arg) -> ext::boolean;

private js_properties:
    DEFINE_GETTER(ctrl_key, ext::boolean);
    DEFINE_GETTER(shift_key, ext::boolean);
    DEFINE_GETTER(alt_key, ext::boolean);
    DEFINE_GETTER(meta_key, ext::boolean);

    DEFINE_GETTER(modifier_alt_graph, ext::boolean);
    DEFINE_GETTER(modifier_caps_lock, ext::boolean);
    DEFINE_GETTER(modifier_fn, ext::boolean);
    DEFINE_GETTER(modifier_fn_lock, ext::boolean);
    DEFINE_GETTER(modifier_hyper, ext::boolean);
    DEFINE_GETTER(modifier_num_lock, ext::boolean);
    DEFINE_GETTER(modifier_scroll_lock, ext::boolean);
    DEFINE_GETTER(modifier_symbol, ext::boolean);
    DEFINE_GETTER(modifier_symbol_lock, ext::boolean);
};


#endif //SBROWSER2_MODIFIER_EVENT_HPP
