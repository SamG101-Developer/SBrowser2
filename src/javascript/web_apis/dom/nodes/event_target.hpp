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
#include USE_INNER_TYPES(dom)
namespace dom::events {class event;}

namespace dom::detail {auto remove_all_event_listeners(nodes::event_target*) -> void;}
namespace dom::detail {auto dispatch(events::event*, nodes::event_target*) -> ext::boolean;}
namespace dom::detail {auto invoke(event_path_struct_t*, events::event*, const ext::number<uchar>&) -> void;}
namespace dom::detail {auto inner_invoke(events::event*, ext::vector_view<ext::map<ext::string, ext::any>>, const ext::number<uchar>&, const ext::boolean&) -> void;}


class dom::nodes::event_target
        : public virtual dom_object
{
public friends:
    friend auto dom::detail::remove_all_event_listeners(
            event_target* event_target) -> void;

    friend auto dom::detail::dispatch(
            events::event* event, nodes::event_target* target) -> ext::boolean;

    friend auto dom::detail::invoke(
            detail::event_path_struct_t* s, events::event* event, const ext::number<uchar>& phase) -> void;

    friend auto dom::detail::inner_invoke(
            events::event* event, ext::vector_view<ext::map<ext::string, ext::any>> event_listeners,
            const ext::number<uchar>& phase, const ext::boolean& invocation_target_in_shadow_tree) -> void;

public constructors:
    DOM_CTORS(event_target);
    event_target() = default;

public js_methods:
    auto    add_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, ext::map<ext::string, ext::any>&& options) -> void;
    auto remove_event_listener(ext::string&& type, detail::event_listener_callback_t&& callback, ext::map<ext::string, ext::any>&& options) -> void;
    auto dispatch_event(events::event* event) -> ext::boolean;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

protected cpp_methods:
    virtual auto get_the_parent(events::event* event) -> event_target*;

private cpp_properties:
    ext::vector<ext::map<ext::string, ext::any>> m_event_listeners;
};


#endif //SBROWSER2_EVENT_TARGET_HPP
