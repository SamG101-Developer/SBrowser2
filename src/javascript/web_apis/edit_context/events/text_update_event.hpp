#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_UPDATE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_UPDATE_EVENT_HPP

#include "dom/events/event.hpp"
namespace edit_context::events {class text_update_event;}

#include "edit_context/events/text_update_event_private.hpp"
namespace edit_context {class text_format;}


class edit_context::events::text_update_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(text_update_event);
    MAKE_PIMPL(text_update_event);
    MAKE_V8_AVAILABLE;
    text_update_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

private js_methods:
    auto get_text_formats() -> ext::vector_view<text_format*>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_UPDATE_EVENT_HPP
