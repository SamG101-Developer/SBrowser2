#ifndef SBROWSER2_EVENT_HPP
#define SBROWSER2_EVENT_HPP

#include "dom_object.hpp"
namespace dom::events {class event;}
namespace dom::events {class event_private;}

#include INCLUDE_INNER_TYPES(dom)
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class event_target;}
namespace dom::nodes {class shadow_root;}


class dom::events::event
        : public virtual dom_object
{
public friends:
    friend class dom::nodes::event_target;
    friend class dom::nodes::shadow_root;

public: constructors
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

    _EXT_NODISCARD auto composed_path() const -> ext::vector<nodes::event_target*>;

public: js_properties
    DEFINE_GETTER(type, ext::string);
    DEFINE_GETTER(bubbles, ext::boolean);
    DEFINE_GETTER(cancelable, ext::boolean);
    DEFINE_GETTER(composed, ext::boolean);

    DEFINE_GETTER(target, nodes::event_target*);
    DEFINE_GETTER(current_target, nodes::event_target*);
    DEFINE_GETTER(related_target, nodes::event_target*);

    DEFINE_GETTER(event_phase, ext::number<ushort>);
    DEFINE_GETTER(time_stamp, ext::number<double>);
    DEFINE_GETTER(is_trusted, ext::boolean);

    DEFINE_GETTER(touch_targets, detail::touch_targets_t);
    DEFINE_GETTER(path, detail::path_t);
};


#endif //SBROWSER2_EVENT_HPP
