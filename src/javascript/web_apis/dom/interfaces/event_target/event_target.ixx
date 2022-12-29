module;
#include "ext/macros.hpp"


export module apis.dom.event_target;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom, event_target)
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(event_target);
    MAKE_PIMPL(event_target);
    MAKE_V8_AVAILABLE(ALL);

public js_methods:
    auto add_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, detail::add_event_listener_options_t&& options = {}) -> void;
    auto add_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, ext::boolean options = {}) -> void;
    auto remove_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, detail::event_listener_options_t&& options = {}) -> void;
    auto remove_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, ext::boolean options = {}) -> void;
    auto dispatch_event(event* event) -> ext::boolean;
};
