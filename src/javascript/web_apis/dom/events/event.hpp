#ifndef SBROWSER2_EVENT_HPP
#define SBROWSER2_EVENT_HPP

#include "dom_object.hpp"
#include "ext/pimpl.hpp"
namespace dom::events {class event;}


#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"
#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(dom)

namespace dom::nodes {class event_target;}
namespace dom::detail {auto dispatch(events::event*, nodes::event_target*) -> ext::boolean;}
namespace dom::detail {auto invoke(event_path_struct_t*, events::event*, ext::number<uchar>) -> void;}
namespace dom::detail {auto inner_invoke(events::event*, ext::vector_view<ext::map<ext::string, ext::any>>, ext::number<uchar>, ext::boolean ) -> void;}


class dom::events::event
        : public virtual dom_object
{
private: aliases
    using touch_targets_t = ext::vector<nodes::event_target*>;
    using path_t = ext::vector<detail::event_path_struct_t*>;

public: friends
    friend class nodes::event_target;

    friend auto dom::detail::dispatch(
            events::event* event, nodes::event_target* target) -> ext::boolean;

    friend auto dom::detail::invoke(
            detail::event_path_struct_t* s, events::event* event, ext::number<uchar> phase) -> void;

    friend auto dom::detail::inner_invoke(
            events::event* event, ext::vector_view<ext::map<ext::string, ext::any>> event_listeners,
            ext::number<uchar> phase, ext::boolean  invocation_target_in_shadow_tree) -> void;

public: constructors
    event() = default;
    event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

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
    ext::property<ext::string>  type;
    ext::property<ext::boolean> bubbles;
    ext::property<ext::boolean> cancelable;
    ext::property<ext::boolean> composed;

    ext::property<nodes::event_target*> target;
    ext::property<nodes::event_target*> current_target;
    ext::property<nodes::event_target*> related_target;

    ext::property<ext::number<ushort>> event_phase;
    ext::property<ext::number<double>> time_stamp;
    ext::property<ext::boolean> is_trusted;

    ext::property<touch_targets_t> touch_targets;
    ext::property<path_t> path;

protected: cpp_members
    MAKE_PIMPL_PROTECTED(event);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_EVENT_HPP
