#ifndef SBROWSER2_CUSTOM_EVENT_HPP
#define SBROWSER2_CUSTOM_EVENT_HPP

#include "dom/events/event.hpp"
namespace dom::events {class custom_event;}


class dom::events::custom_event final
        : public event
{
public constructors:
    custom_event() = default;
    custom_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<ext::any> detail;

public cpp_members:
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_CUSTOM_EVENT_HPP
