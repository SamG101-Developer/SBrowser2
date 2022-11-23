#ifndef SBROWSER2_CUSTOM_EVENT_HPP
#define SBROWSER2_CUSTOM_EVENT_HPP

#include "dom/events/event.hpp"
namespace dom::events {class custom_event;}
namespace dom::events {class custom_event_private;}


class dom::events::custom_event final
        : public event
{
public constructors:
    custom_event() = default;
    custom_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(custom_event);
    MAKE_V8_AVAILABLE(ALL);

private js_properties:
    DEFINE_GETTER(detail, ext::any) {return d_ptr->detail;};
};


#endif //SBROWSER2_CUSTOM_EVENT_HPP
