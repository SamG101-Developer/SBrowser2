#pragma once
#ifndef SBROWSER2_EVENT_TARGET_HPP
#define SBROWSER2_EVENT_TARGET_HPP

#include "dom_object.hpp"
namespace dom::nodes {class event_target;}

#include "ext/boolean.hpp"
#include "ext/keywords.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <functional>
namespace dom::events {class event;}


class dom::nodes::event_target
        : public virtual web_apis::dom_object
{
private aliases:
    // TODO : parameters optional (in v8::Function conversion?)
    using event_listener_callback_t = std::function<void(ext::string, events::event*)>;

public constructors:
    event_target();
    ~event_target() override;

public js_methods:
    auto    add_event_listener(ext::string&& type, event_listener_callback_t&& callback, ext::string_any_map& options) -> void;
    auto remove_event_listener(ext::string&& type, event_listener_callback_t&& callback, ext::string_any_map& options) -> void;
    auto dispatch_event(events::event* event) -> ext::boolean;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

protected cpp_methods:
    virtual auto get_the_parent(events::event* event) -> event_target*;

private cpp_properties:
    ext::vector<ext::string_any_map> m_event_listeners;
};


#endif //SBROWSER2_EVENT_TARGET_HPP
