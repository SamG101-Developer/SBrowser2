#pragma once
#ifndef SBROWSER2_EVENT_TARGET_HPP
#define SBROWSER2_EVENT_TARGET_HPP

#include "dom_object.hpp"
namespace dom::nodes {class event_target;}
namespace dom::nodes {class event_target_private;}

#include INCLUDE_INNER_TYPES(dom)
#include "ext/boolean.ixx"
#include "ext/functional.ixx"
#include "ext/keywords.hpp"
#include "ext/map.ixx"
#include "ext/string.hpp"
#include "ext/type_traits.ixx"
#include "ext/vector.hpp"
namespace dom::events {class event;}


class dom::nodes::event_target
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(event_target);
    MAKE_PIMPL(event_target);
    MAKE_V8_AVAILABLE(ALL);

public js_methods:
    auto add_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, ext::variant<detail::add_event_listener_options_t, ext::boolean>&& options = {}) -> void;
    auto remove_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, ext::variant<detail::event_listener_options_t, ext::boolean>&& options = {}) -> void;
    auto dispatch_event(events::event* event) -> ext::boolean;
};


#endif //SBROWSER2_EVENT_TARGET_HPP
