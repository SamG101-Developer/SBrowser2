#ifndef SBROWSER2_WINDOW_HPP
#define SBROWSER2_WINDOW_HPP

#include "dom/nodes/event_target.hpp"
namespace dom::nodes {class window;}

#include "ext/threading.hpp"
#include "ext/type_traits.hpp"
#include "ext/queue.hpp"
#include "ext/vector.hpp"
#include "ext/vector_like.hpp"
#include USE_INNER_TYPES(background_tasks)
#include USE_INNER_TYPES(dom)
#include USE_INNER_TYPES(html)
namespace background_tasks {class idle_deadline;}
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace dom::nodes {class window_proxy;}
namespace html::other {class custom_element_registry;}
namespace html::other {class bar_prop;}
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

    ext::property<std::unique_ptr<html::other::bar_prop>> location_bar;
    ext::property<std::unique_ptr<html::other::bar_prop>> menu_bar;
    ext::property<std::unique_ptr<html::other::bar_prop>> personal_bar;
    ext::property<std::unique_ptr<html::other::bar_prop>> scroll_bars;
    ext::property<std::unique_ptr<html::other::bar_prop>> status_bar;
    ext::property<std::unique_ptr<html::other::bar_prop>> tool_bar;

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
    high_resolution_time::detail::dom_high_res_time_stamp_t last_activation_timestamp;

    /* BACKGROUND_TASKS */
    ext::vector<background_tasks::detail::idle_request_callback_t> m_idle_request_callbacks;
    ext::vector<background_tasks::detail::idle_request_callback_t> m_runnable_idle_callbacks;
    ext::number<ulong> m_idle_callback_identifier;
    ext::queue<std::jthread> m_current_threads;
    std::condition_variable m_condition_variable;
    std::mutex m_mutex;

    /* EVENT_TIMING */
    // TODO

private cpp_accessors:
    DEFINE_GETTER(name);
    DEFINE_GETTER(closed);

    DEFINE_SETTER(name);
};


#endif //SBROWSER2_WINDOW_HPP
