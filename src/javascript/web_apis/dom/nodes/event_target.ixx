module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.event_target;
import apis._.dom_object;
import apis.dom.types;
import ext.boolean;
import ext.string;
import ext.tuple;
import js.env.module_type;

namespace dom {class event;}


DEFINE_PUBLIC_CLASS(dom, event_target)
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(event_target);
    MAKE_PIMPL(event_target);
    MAKE_V8_AVAILABLE(ALL);

public js_methods:
    template <ext::type_is<detail::add_event_listener_options_t, ext::boolean> T>
    auto add_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, T&& options = {}) -> void;

    template <ext::type_is<detail::event_listener_options_t, ext::boolean> T>
    auto remove_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, T&& options = {}) -> void;

    auto dispatch_event(event* event) -> ext::boolean;
};
