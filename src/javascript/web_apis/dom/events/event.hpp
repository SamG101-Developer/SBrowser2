#ifndef SBROWSER2_EVENT_HPP
#define SBROWSER2_EVENT_HPP

#include "dom_object.hpp"
namespace dom::events {class event;}

#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(dom)
namespace dom::nodes {class event_target;}
namespace dom::detail {auto dispatch(events::event*, nodes::event_target*) -> ext::boolean;}
namespace dom::detail {auto invoke(event_path_struct_t*, events::event*, const ext::number<uchar>&) -> void;}
namespace dom::detail {auto inner_invoke(events::event*, ext::vector_view<ext::map<ext::string, ext::any>>, const ext::number<uchar>&, const ext::boolean&) -> void;}


class dom::events::event
        : public virtual dom_object
{
private: aliases
    using touch_targets_t = ext::vector<nodes::event_target*>;
    using path_t          = ext::vector<detail::event_path_struct_t*>;

public: friends
    friend class nodes::event_target;

    friend auto dom::detail::dispatch(
            events::event* event, nodes::event_target* target) -> ext::boolean;

    friend auto dom::detail::invoke(
            detail::event_path_struct_t* s, events::event* event, const ext::number<uchar>& phase) -> void;

    friend auto dom::detail::inner_invoke(
            events::event* event, ext::vector_view<ext::map<ext::string, ext::any>> event_listeners,
            const ext::number<uchar>& phase, const ext::boolean& invocation_target_in_shadow_tree) -> void;

public: constructors
    DOM_CTORS(event);
    event() = default;
    event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public: js_static_constants
    static constexpr unsigned short NONE = 0;
    static constexpr unsigned short CAPTURING_PHASE = 1;
    static constexpr unsigned short AT_TARGET = 2;
    static constexpr unsigned short BUBBLING_PHASE = 3;

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

    ext::property<std::unique_ptr<nodes::event_target>> target;
    ext::property<std::unique_ptr<nodes::event_target>> current_target;
    ext::property<std::unique_ptr<nodes::event_target>> related_target;

    ext::property<ext::number<ushort>> event_phase;
    ext::property<ext::number<double>> time_stamp;
    ext::property<ext::boolean> is_trusted;

    ext::property<std::unique_ptr<touch_targets_t>> touch_targets;
    ext::property<std::unique_ptr<path_t>> path;

public: cpp_methods
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private: cpp_properties
    bool m_stop_propagation_flag = false;
    bool m_stop_immediate_propagation_flag = false;
    bool m_canceled_flag = false;
    bool m_in_passive_listener_flag = false;
    bool m_initialized_flag = true;
    bool m_dispatch_flag = false;
};


#endif //SBROWSER2_EVENT_HPP
