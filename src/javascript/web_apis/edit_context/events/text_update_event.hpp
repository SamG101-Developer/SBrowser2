#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_UPDATE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_UPDATE_EVENT_HPP

#include "dom/events/event.hpp"
namespace edit_context::events {class text_update_event;}


class edit_context::events::text_update_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(text_update_event);
    text_update_event() = default;
    text_update_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<ext::number<ulong>> update_range_start;
    ext::property<ext::number<ulong>> update_range_end;
    ext::property<ext::number<ulong>> selection_start;
    ext::property<ext::number<ulong>> selection_end;
    ext::property<ext::number<ulong>> composition_start;
    ext::property<ext::number<ulong>> composition_end;
    ext::property<ext::string> text;

public cpp_properties:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_EDIT_CONTEXT_TEXT_UPDATE_EVENT_HPP
