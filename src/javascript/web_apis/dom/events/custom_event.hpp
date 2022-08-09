#ifndef SBROWSER2_CUSTOM_EVENT_HPP
#define SBROWSER2_CUSTOM_EVENT_HPP

#include "dom/events/event.hpp"
namespace dom::events {class custom_event;}


class dom::events::custom_event final
        : public event
{
public constructors:
    DOM_CTORS(custom_event);
    custom_event() = default;
    custom_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<ext::any> detail;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_CUSTOM_EVENT_HPP
