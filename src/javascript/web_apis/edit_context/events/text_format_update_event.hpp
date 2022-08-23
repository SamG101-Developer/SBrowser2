#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_FORMAT_UPDATE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_FORMAT_UPDATE_EVENT_HPP

#include "dom/events/event.hpp"
namespace edit_context {class text_format;}
namespace edit_context::events {class text_format_update_event;}


class edit_context::events::text_format_update_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(text_format_update_event);
    text_format_update_event() = default;
    text_format_update_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_methods:
    auto get_text_formats() -> ext::vector<text_format*>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_EVENTS_TEXT_FORMAT_UPDATE_EVENT_HPP
