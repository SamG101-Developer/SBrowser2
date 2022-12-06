module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/extended_attributes.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.event;
import apis._.dom_object;
import apis.dom.types;
import ext.any;
import ext.boolean;
import ext.map;
import ext.string;
import ext.tuple;
import ext.number;
import ext.vector;
import js.env.module_type;

namespace dom {class document;}
namespace dom {class event_target;}
namespace dom {class shadow_root;}


DEFINE_PUBLIC_CLASS(dom, event)
        : public virtual dom_object
{
public friends:
    friend class dom::document;
    friend class dom::event_target;
    friend class dom::shadow_root;
    
public typedefs:
    using event_init_t = ext::map<ext::string, ext::any>;
    using touch_targets_t = ext::vector<event_target*>;
    using path_t = ext::vector<std::unique_ptr<detail::event_path_struct_t>>;

public constructors:
    event(ext::string&& event_type, event_init_t&& event_init = {});
    MAKE_PIMPL(event);
    MAKE_V8_AVAILABLE(ALL);

public js_static_constants:
    constexpr static const ext::number<ushort> NONE = 0;
    constexpr static const ext::number<ushort> CAPTURING_PHASE = 1;
    constexpr static const ext::number<ushort> AT_TARGET = 2;
    constexpr static const ext::number<ushort> BUBBLING_PHASE = 3;

public js_methods:
    auto stop_propagation() -> void;
    auto stop_immediate_propagation() -> void;
    auto prevent_default() -> void;

    _EXT_NODISCARD auto composed_path() const -> ext::vector<event_target*>;

public js_properties:
    DEFINE_GETTER(type, ext::string);
    DEFINE_GETTER(bubbles, ext::boolean);
    DEFINE_GETTER(cancelable, ext::boolean);
    DEFINE_GETTER(composed, ext::boolean);

    DEFINE_GETTER(target, event_target*);
    DEFINE_GETTER(current_target, event_target*);
    DEFINE_GETTER(related_target, event_target*);

    DEFINE_GETTER(event_phase, ext::number<ushort>);
    DEFINE_GETTER(time_stamp, ext::number<double>);
    DEFINE_GETTER(is_trusted, ext::boolean);

    DEFINE_GETTER(touch_targets, touch_targets_t);
    DEFINE_GETTER(path, path_t);
};
