#pragma once
#ifndef SBROWSER2_EVENT_TARGET_HPP
#define SBROWSER2_EVENT_TARGET_HPP

#include <web_apis/dom_object.hpp>

namespace dom::nodes {class event_target;}

#include <functional>

#include <ext/boolean.hpp>
#include <ext/keywords.hpp>
#include <ext/map.hpp>
#include <ext/string.hpp>
#include <ext/vector.hpp>

namespace dom::events {class event;}
namespace dom::detail::event_internals {auto    add_event_listener(nodes::event_target* event_target, const ext::string_any_map& event_listener) -> void;}
namespace dom::detail::event_internals {auto remove_event_listener(nodes::event_target* event_target, const ext::string_any_map& event_listener) -> void;}
namespace dom::detail::event_internals {auto remove_all_event_listeners(nodes::event_target* event_target) -> void;}


class dom::nodes::event_target
        : public virtual web_apis::dom_object
{
private aliases:
    using event_listener_callback_t = std::function<void()>;

public friends:
    friend auto detail::event_internals::   add_event_listener(nodes::event_target* event_target, const ext::string_any_map& event_listener) -> void;
    friend auto detail::event_internals::remove_event_listener(nodes::event_target* event_target, const ext::string_any_map& event_listener) -> void;
    friend auto detail::event_internals::remove_all_event_listeners(nodes::event_target* event_target) -> void;

public constructors:
    using dom_object::dom_object;
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
