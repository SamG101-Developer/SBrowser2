#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_UI_EVENTS_MIXINS_MODIFIER_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_UI_EVENTS_MIXINS_MODIFIER_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "ui_events/ui_event_private.hpp"




DEFINE_PRIVATE_CLASS(ui_events::mixins, modifier_event) : ui_events::ui_event_private
{
    ext::boolean ctrl_key;
    ext::boolean shift_key;
    ext::boolean alt_key;
    ext::boolean meta_key;

    ext::boolean modifier_alt_graph;
    ext::boolean modifier_caps_lock;
    ext::boolean modifier_fn;
    ext::boolean modifier_fn_lock;
    ext::boolean modifier_hyper;
    ext::boolean modifier_num_lock;
    ext::boolean modifier_scroll_lock;
    ext::boolean modifier_symbol;
    ext::boolean modifier_symbol_lock;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_UI_EVENTS_MIXINS_MODIFIER_EVENT_PRIVATE_HPP
