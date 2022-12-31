module;
#include "ext/macros.hpp"


export module apis.dom.window;
import apis.dom.event_target;
import apis.html.mixins.window_or_worker_global_scope;
import ext.vector_like;

IMPORT_ALL_TYPES(background_tasks);
IMPORT_ALL_TYPES(css.cssom);
IMPORT_ALL_TYPES(dom);
IMPORT_ALL_TYPES(html);
IMPORT_ALL_TYPES(selection);


DEFINE_PUBLIC_CLASS(dom, window) final
        : public dom::event_target
        , public html::window_or_worker_global_scope
        , public ext::vector_like<html::detail::browsing_context_t*>
{
public typedefs:
    using window_post_message_options_t = ext::map<ext::string, ext::any>;
    using idle_request_options_t = ext::map<ext::string, ext::any>;

public constructors:
    DOM_CTORS(window);
    MAKE_PIMPL(window);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    /* [HTML] */
    auto close() -> void;
    auto stop() -> void;
    auto focus() -> void;
    auto blur() -> void;

    auto open(ext::string_view url = u"", ext::string_view target = u"_blank", ext::string_view features = u"") -> window_proxy;

    auto alert(ext::string&& message = u"") -> void;
    auto confirm(ext::string&& message = u"") -> ext::boolean;
    auto prompt(ext::string&& message = u"", ext::string&& default_ = u"") -> ext::string;
    auto print() -> void;

    auto post_message(ext::any&& message, ext::string_view target_origin = u"/", ext::vector_span<ext::any> transfer = {}) -> void;
    auto post_message(ext::any&& message, window_post_message_options_t&& options = {}) -> void;

    /* [BACKGROUND-TASKS] */
    auto request_idle_callback(background_tasks::detail::idle_request_callback_t&& callback, idle_request_options_t&& options) -> ext::number<ulong>;
    auto cancel_idle_task(ext::number<ulong> handle) -> void;

    /* [SELECTION] */
    auto get_selection() -> selection::selection*;

    /* [CSSOM] */
    auto get_computed_style(element* element, ext::string_view pseudo_element = u"") -> std::unique_ptr<css::cssom::css_style_declaration>;

private js_properties:
    /* [HTML] */
    DEFINE_GETTER(window, window_proxy*);
    DEFINE_GETTER(document, document*);
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(location, html::location*);
    DEFINE_GETTER(history, html::history*);
    DEFINE_GETTER(custom_elements, html::custom_element_registry*);
    DEFINE_GETTER(closed, ext::boolean);
    DEFINE_GETTER(top, window_proxy*);
    DEFINE_GETTER(opener, window_proxy*);
    DEFINE_GETTER(parent, window_proxy*);
    DEFINE_GETTER(frame_element, element*);
    DEFINE_GETTER(navigator, html::navigator*);
    DEFINE_GETTER(origin_agent_cluster, ext::boolean);

    DEFINE_SETTER(name, ext::string);
    DEFINE_SETTER(opener, window_proxy*);
    DEFINE_SETTER(frame_element, element*);
};

