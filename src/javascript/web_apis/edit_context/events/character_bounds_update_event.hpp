#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_CHARACTER_BOUNDS_UPDATE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_CHARACTER_BOUNDS_UPDATE_EVENT_HPP

#include "dom/events/event.hpp"
namespace edit_context::events {class character_bounds_update_event;}

#include "edit_context/events/character_bounds_update_event_private.hpp"


class edit_context::events::character_bounds_update_event
        : public dom::events::event
{
public constructors:
    character_bounds_update_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    DOM_CTORS(character_bounds_update_event);
    MAKE_PIMPL(character_bounds_update_event);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(range_start, ext::number<ulong>);
    DEFINE_GETTER(range_end, ext::number<ulong>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_CHARACTER_BOUNDS_UPDATE_EVENT_HPP
