#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_FORMAT_UPDATE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_FORMAT_UPDATE_EVENT_HPP

#include "dom/events/event.hpp"
#include "edit_context/text_format.hpp"
namespace edit_context {class text_format;}
namespace edit_context::events {class text_format_update_event;}




class edit_context::events::text_format_update_event
        : public dom::events::event
        , public edit_context::text_format
{
public constructors:
    text_format_update_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    DOM_CTORS(text_format_update_event);
    MAKE_PIMPL(text_format_update_event);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto get_text_formats() -> ranges::any_helpful_view<text_format*>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_FORMAT_UPDATE_EVENT_HPP
