#ifndef SBROWSER2_WINDOW_HPP
#define SBROWSER2_WINDOW_HPP

#include "dom/nodes/event_target.hpp"
#include "ext/vector_like.hpp"
namespace dom::nodes {class window;}

#include "ext/threading.hpp"
#include "ext/type_traits.hpp"
#include "ext/queue.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(background_tasks)
#include USE_INNER_TYPES(dom)
#include USE_INNER_TYPES(html)
namespace background_tasks {class idle_deadline;}
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace dom::nodes {class window_proxy;}
namespace event_timing {class performance_event_timing;}
namespace event_timing {class event_counts;}
namespace event_timing {class interaction_counts;}
namespace html::other {class custom_element_registry;}
namespace html::other {class history;}
namespace html::other {class location;}
namespace html::other {class navigator;}
namespace selection {class selection;}


class dom::nodes::window final
        : public event_target
        , public ext::vector_like<html::detail::browsing_context_t*>
{
public js_properties:
    /* HTML */
    ext::property<std::unique_ptr<window_proxy>> window;
    ext::property<std::unique_ptr<window_proxy>> self;
    ext::property<std::unique_ptr<document>> document;
    ext::property<ext::string> name;

    ext::property<std::unique_ptr<html::other::location>> location;
    ext::property<std::unique_ptr<html::other::history>> history;
    ext::property<std::unique_ptr<html::other::custom_element_registry>> custom_elements;

    ext::property<ext::string> status;
    ext::property<ext::boolean> closed;

    ext::property<std::unique_ptr<window_proxy>> frames;
    ext::property<std::unique_ptr<window_proxy>> top;
    ext::property<std::unique_ptr<window_proxy>> parent;
    ext::property<ext::any> opener;
    ext::property<std::unique_ptr<dom::nodes::element>> frame_element;

    ext::property<std::unique_ptr<html::other::navigator>> navigator;
    ext::property<ext::boolean> origin_agent_cluster;

public js_methods:
    /* HTML */
    auto close() -> void;
    auto stop() -> void;
    auto focus() -> void;
    auto blur() -> void;

    auto open(ext::string_view url = "", ext::string_view targtet = "_blank", ext::string_view features = "") -> window_proxy;

    auto alert(ext::string&& message = "") -> void;
    auto confirm(ext::string&& message = "") -> ext::boolean;
    auto prompt(ext::string&& message = "", ext::string&& default_ = "") -> ext::string;
    auto print() -> void;

    auto post_message(ext::any&& message, ext::string_view target_origin = "/", ext::vector_view<ext::any> transfer = {}) -> void;
    auto post_message(ext::any&& message, detail::window_post_message_options_t&& options = {}) -> void;

    /* BACKGROUND_TASKS */
    auto request_idle_callback(
            background_tasks::detail::idle_request_callback_t&& callback,
            background_tasks::detail::idle_request_options_t&& options)
            -> ext::number<ulong>;

    auto cancel_idle_task(
            const ext::number<ulong>& handle)
            -> void;

    /* SELECTION */
    auto get_selection() -> selection::selection*;

private js_slots:
    ext::slot<html::detail::cross_origin_property_descriptor_map_t> s_cross_origin_property_descriptor_map;

private cpp_properties:
    /* HTML */
    ext::boolean m_has_dispatched_scroll_event = false;
    std::unique_ptr<dom::detail::custom_element_reactions_stack_t> m_custom_element_reaction_stack;
    ext::queue<dom::nodes::element*>* m_current_element_queue;
    hr_time::dom_high_res_time_stamp last_activation_timestamp;

    /* BACKGROUND_TASKS */
    ext::vector<background_tasks::detail::idle_request_callback_t> m_idle_request_callbacks;
    ext::vector<background_tasks::detail::idle_request_callback_t> m_runnable_idle_callbacks;
    ext::number<ulong> m_idle_callback_identifier;
    ext::queue<std::jthread> m_current_threads;
    std::condition_variable m_condition_variable;
    std::mutex m_mutex;

    /* EVENT_TIMING */
    ext::vector<event_timing::performance_event_timing*> m_entries_to_be_queued;
    std::unique_ptr<event_timing::performance_event_timing> m_pending_first_pointer_down;
    ext::boolean m_has_dispatched_input_event;
    ext::number<short> m_user_interaction_value = ext::number<int>::random(100, 10000);
    ext::map<ext::number<int>, event_timing::performance_event_timing*> m_pending_key_downs;
    ext::map<ext::number<int>, event_timing::performance_event_timing*> m_pending_pointer_downs;
    ext::map<ext::number<int>, ext::number<int>> m_pointer_interaction_value_map;
    ext::set<ext::number<int>> m_pointer_is_drag_set;
    std::unique_ptr<event_timing::event_counts> m_event_counts;
    std::unique_ptr<event_timing::interaction_counts> m_interaction_counts;

private cpp_accessors:
    DEFINE_GETTER(name);
    DEFINE_GETTER(closed);

    DEFINE_SETTER(name);
};


#endif //SBROWSER2_WINDOW_HPP
