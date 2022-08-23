#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_CHARACTER_BOUNDS_UPDATE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_CHARACTER_BOUNDS_UPDATE_EVENT_HPP

#include "dom/events/event.hpp"
namespace edit_context::events {class character_bounds_update_event;}


class edit_context::events::character_bounds_update_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(character_bounds_update_event);
    character_bounds_update_event() = default;
    character_bounds_update_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<ext::number<ulong>> range_start;
    ext::property<ext::number<ulong>> range_end;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_CHARACTER_BOUNDS_UPDATE_EVENT_HPP
