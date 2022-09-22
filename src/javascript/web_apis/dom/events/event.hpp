#ifndef SBROWSER2_EVENT_HPP
#define SBROWSER2_EVENT_HPP

#include "dom_object.hpp"
namespace dom::events {class event;}


#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"
#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(dom)


#include "dom/events/event_private.hpp"


class dom::events::event
        : public virtual dom_object
{
public: constructors
    event() = default;
    event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

    MAKE_PIMPL(event);
    MAKE_V8_AVAILABLE;

public: js_static_constants
    constexpr static const ext::number<ushort> NONE = 0;
    constexpr static const ext::number<ushort> CAPTURING_PHASE = 1;
    constexpr static const ext::number<ushort> AT_TARGET = 2;
    constexpr static const ext::number<ushort> BUBBLING_PHASE = 3;

public: js_methods
    auto stop_propagation() -> void;
    auto stop_immediate_propagation() -> void;
    auto prevent_default() -> void;

    [[nodiscard]] auto composed_path() const -> ext::vector<nodes::event_target*>;

public: js_properties
    DEFINE_GETTER(type, ext::string) {return d_ptr->type;}
    DEFINE_GETTER(bubbles, ext::boolean) {return d_ptr->bubbles;}
    DEFINE_GETTER(cancelable, ext::boolean) {return d_ptr->cancelable;}
    DEFINE_GETTER(composed, ext::boolean) {return d_ptr->composed;}

    DEFINE_GETTER(target, nodes::event_target*) {return d_ptr->target;}
    DEFINE_GETTER(current_target, nodes::event_target*) {return d_ptr->current_target;}
    DEFINE_GETTER(related_target, nodes::event_target*) {return d_ptr->related_target;}

    DEFINE_GETTER(event_phase, ext::number<ushort>) {return d_ptr->event_phase;}
    DEFINE_GETTER(time_stamp, ext::number<double>) {return d_ptr->time_stamp;}
    DEFINE_GETTER(is_trusted, ext::boolean) {return d_ptr->is_trusted;}

    DEFINE_GETTER(touch_targets, detail::touch_targets_t) {return d_ptr->touch_targets;}
    DEFINE_GETTER(path, detail::path_t) {return d_ptr->path;}
};


#endif //SBROWSER2_EVENT_HPP
