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

private js_methods:
    template <ext::type_is<this_private_t::add_event_listener_options_t, ext::boolean T> T>
    auto add_event_listener(ext::string&& type, this_private_t::event_listener_callback_t&& callback, T&& options = {}) -> void;

    template <ext::type_is<this_private_t::event_listener_options_t, ext::boolean> T>
    auto remove_event_listener(ext::string&& type, this_private_t::event_listener_callback_t&& callback, T&& options = {}) -> void;

    auto dispatch_event(event* event) -> ext::boolean;
};
