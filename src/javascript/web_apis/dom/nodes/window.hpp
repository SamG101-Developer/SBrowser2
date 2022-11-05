#ifndef SBROWSER2_WINDOW_HPP
#define SBROWSER2_WINDOW_HPP

#include "dom/nodes/event_target.hpp"
#include "ext/vector_like.hpp"
#include "html/mixins/window_or_worker_global_scope.hpp"
namespace dom::nodes {class window;}
namespace dom::nodes {class window_private;}

#include "ext/span.hpp"
#include "ext/threading.hpp"
#include "ext/type_traits.hpp"
#include "ext/queue.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(background_tasks)
#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(html)
namespace background_tasks {class idle_deadline;}
namespace css::cssom::other {class css_style_declaration;}
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
        , public html::mixins::window_or_worker_global_scope
{
public constructors:
    DOM_CTORS(window);
    MAKE_PIMPL(window);
    MAKE_V8_AVAILABLE;

public js_methods:
    /* [HTML] */
    auto close() -> void;
    auto stop() -> void;
    auto focus() -> void;
    auto blur() -> void;

    auto open(ext::string_view url = u8"", ext::string_view targtet = u8"_blank", ext::string_view features = u8"") -> window_proxy;

    auto alert(ext::string&& message = u8"") -> void;
    auto confirm(ext::string&& message = u8"") -> ext::boolean;
    auto prompt(ext::string&& message = u8"", ext::string&& default_ = u8"") -> ext::string;
    auto print() -> void;

    auto post_message(ext::any&& message, ext::string_view target_origin = u8"/", ext::vector_span<ext::any> transfer = {}) -> void;
    auto post_message(ext::any&& message, detail::window_post_message_options_t&& options = {}) -> void;

    /* [BACKGROUND-TASKS] */
    auto request_idle_callback(background_tasks::detail::idle_request_callback_t&& callback, background_tasks::detail::idle_request_options_t&& options) -> ext::number<ulong>;
    auto cancel_idle_task(ext::number<ulong> handle) -> void;

    /* [SELECTION] */
    auto get_selection() -> selection::selection*;

    /* [CSSOM] */
    auto get_computed_style(element* element, ext::string_view pseudo_element = u8"") -> css::cssom::other::css_style_declaration;

private js_properties:
    /* [HTML] */
    DEFINE_GETTER(window, window_proxy*);
    DEFINE_GETTER(document, document*);
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(location, html::other::location*);
    DEFINE_GETTER(history, html::other::history*);
    DEFINE_GETTER(custom_elements, html::other::custom_element_registry*);
    DEFINE_GETTER(closed, ext::boolean);
    DEFINE_GETTER(top, window_proxy*);
    DEFINE_GETTER(opener, window_proxy*);
    DEFINE_GETTER(parent, window_proxy*);
    DEFINE_GETTER(frame_element, dom::nodes::element*);
    DEFINE_GETTER(navigator, html::other::navigator*);
    DEFINE_GETTER(origin_agent_cluster, ext::boolean);

    DEFINE_SETTER(name, ext::string);
    DEFINE_SETTER(opener, window_proxy*);
    DEFINE_SETTER(frame_element, dom::nodes::element*);
};


#endif //SBROWSER2_WINDOW_HPP
