#ifndef SBROWSER2_CUSTOM_EVENT_HPP
#define SBROWSER2_CUSTOM_EVENT_HPP

#include <web_apis/dom/events/event.hpp>
namespace dom::events {class custom_event;}


class dom::events::custom_event final
        : public event
{
public constructors:
    using event::event;
    custom_event(ext::string_view event_type, ext::string_any_map_view event_init = {});

public js_properties:
    ext::property<ext::any> detail;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_CUSTOM_EVENT_HPP
