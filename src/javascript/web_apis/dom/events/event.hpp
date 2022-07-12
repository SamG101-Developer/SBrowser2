#ifndef SBROWSER2_EVENT_HPP
#define SBROWSER2_EVENT_HPP

#include "dom_object.hpp"
namespace dom::events {class event;}

#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
namespace dom::nodes {class event_target;}
namespace dom::detail::event_internals {struct event_path_struct;}


class dom::events::event
        : public virtual web_apis::dom_object
{
private: aliases
    using touch_targets_t = ext::vector<nodes::event_target*>;
    using path_t          = ext::vector<detail::event_internals::event_path_struct*>;

public: friends
    friend class nodes::event_target;

public: constructors
    event() = default;
    event(ext::string_view event_type, ext::string_any_map_view event_init = {});

public: js_static_constants
    static constexpr unsigned short NONE            = 0;
    static constexpr unsigned short CAPTURING_PHASE = 1;
    static constexpr unsigned short AT_TARGET       = 2;
    static constexpr unsigned short BUBBLING_PHASE  = 3;

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
    ext::property<std::unique_ptr<path_t         >> path;

public: cpp_methods
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private: cpp_properties
    bool m_stop_propagation_flag           = false;
    bool m_stop_immediate_propagation_flag = false;
    bool m_canceled_flag                   = false;
    bool m_in_passive_listener_flag        = false;
    bool m_initialized_flag                = true;
    bool m_dispatch_flag                   = false;
};


#endif //SBROWSER2_EVENT_HPP
