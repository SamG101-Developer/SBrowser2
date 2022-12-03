#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_CHARACTER_BOUNDS_UPDATE_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_CHARACTER_BOUNDS_UPDATE_EVENT_PRIVATE_HPP

#include "dom/events/event_private.hpp"

#include "ext/pimpl.ixx"


DEFINE_PRIVATE_CLASS(edit_context::events, character_bounds_update_event)
        : dom::events::event_private
{
    MAKE_QIMPL(character_bounds_update_event);
    ext::number<ulong> range_start;
    ext::number<ulong> range_end;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_CHARACTER_BOUNDS_UPDATE_EVENT_PRIVATE_HPP
