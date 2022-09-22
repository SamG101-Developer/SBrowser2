#pragma once
#ifndef SBROWSER2_EVENT_TARGET_HPP
#define SBROWSER2_EVENT_TARGET_HPP

#include "dom_object.hpp"
namespace dom::nodes {class event_target;}

#include "ext/boolean.hpp"
#include "ext/functional.hpp"
#include "ext/keywords.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(dom)
namespace dom::events {class event;}

namespace dom::detail {auto remove_all_event_listeners(nodes::event_target*) -> void;}
namespace dom::detail {auto dispatch(events::event*, nodes::event_target*) -> ext::boolean;}
namespace dom::detail {auto invoke(event_path_struct_t*, events::event*, ext::number<uchar>) -> void;}
namespace dom::detail {auto inner_invoke(events::event*, ext::vector_view<ext::map<ext::string, ext::any>>, ext::number<uchar>, ext::boolean ) -> void;}

#include "dom/nodes/event_target_private.hpp"


class dom::nodes::event_target
        : public virtual dom_object
{
public friends:
    friend auto dom::detail::remove_all_event_listeners(
            event_target* event_target) -> void;

    friend auto dom::detail::dispatch(
            events::event* event, nodes::event_target* target) -> ext::boolean;

    friend auto dom::detail::invoke(
            detail::event_path_struct_t* s, events::event* event, ext::number<uchar> phase) -> void;

    friend auto dom::detail::inner_invoke(
            events::event* event, ext::vector_view<ext::map<ext::string, ext::any>> event_listeners,
            ext::number<uchar> phase, ext::boolean  invocation_target_in_shadow_tree) -> void;

public constructors:
    DOM_CTORS(event_target);
    event_target();

public js_methods:
    auto    add_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, ext::variant<detail::add_event_listener_options_t, ext::boolean> options = {}) -> void;
    auto remove_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, ext::variant<detail::event_listener_options_t, ext::boolean> options = {}) -> void;
    auto dispatch_event(events::event* event) -> ext::boolean;

public cpp_members:
    MAKE_PIMPL(event_target);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_EVENT_TARGET_HPP
