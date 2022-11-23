#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_FORMAT_UPDATE_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_FORMAT_UPDATE_EVENT_PRIVATE_HPP

#include "dom/events/event_private.hpp"
#include "edit_context/text_format_private.hpp"

#include "ext/pimpl.hpp"


DEFINE_PRIVATE_CLASS(edit_context::events, text_format_update_event)
        : dom::events::event_private
        , text_format_private
{
    MAKE_QIMPL(text_format_update_event);

    ext::vector<std::unique_ptr<text_format>> text_formats;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_FORMAT_UPDATE_EVENT_PRIVATE_HPP
