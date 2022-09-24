#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_UPDATE_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_UPDATE_EVENT_PRIVATE_HPP

#include "dom/events/event_private.hpp"

#include "ext/pimpl.hpp"


DEFINE_PRIVATE_CLASS(edit_context::events, text_update_event) : dom::events::event_private
{
    ext::number<ulong> update_range_start;
    ext::number<ulong> update_range_end;
    ext::number<ulong> selection_start;
    ext::number<ulong> selection_end;
    ext::number<ulong> composition_start;
    ext::number<ulong> composition_end;
    ext::string text;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_UPDATE_EVENT_PRIVATE_HPP
