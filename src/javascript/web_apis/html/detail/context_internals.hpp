#ifndef SBROWSER2_CONTEXT_INTERNALS_HPP
#define SBROWSER2_CONTEXT_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/pair.hpp"
#include "ext/vector.hpp"
#include "url/url.hpp"
#include <memory>
#include USE_INNER_TYPES(html)
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace dom::nodes {class window_proxy;}
namespace html::detail::policy_internals {struct policy_container;}

namespace html::detail
{

    auto is_still_on_initial(
            browsing_context* context)
            -> ext::boolean;

    auto choose_browsing_context(
            ext::string_view name,
            browsing_context* context,
            ext::boolean&& noopener = false)
            -> ext::pair<browsing_context*, ext::string>;

    template <callable F>
    auto navigate(
            browsing_context* context,
            browsing_context* source_context = nullptr,
            ext::boolean&& exceptions_enabled = false,
            history_handling_behaviour_t history_handling_behaviour = history_handling_behaviour_t::DEFAULT,
            html::detail::policy_internals::policy_container* history_policy_container = nullptr,
            ext::string_view navigation_type = "",
            ext::string_view navigation_id = "",
            F&& process_response_end_of_body = []() {})
            -> void;

    auto create_new_nested_browsing_context(
            dom::nodes::element* element)
            -> void;

    auto is_ancestor_browsing_context(
            browsing_context* context_a,
            browsing_context* context_b)
            -> ext::boolean;

    auto ancestor_browsing_contexts(
            browsing_context* context_a)
            -> ext::vector<browsing_context*>;
}


struct html::detail::browsing_context
{
    std::unique_ptr<dom::nodes::window_proxy> window_proxy;
    std::unique_ptr<browsing_context> opener_browsing_context;
    ext::boolean disowned;
    ext::boolean is_closing;

    std::unique_ptr<dom::nodes::document> container_document;

    ext::string creator_origin;
    url::url_object creator_url;
    url::url_object creator_base_url;

    browsing_context* parent_browsing_context;
    ext::vector<dom::nodes::document*> session_history {};

    auto active_window() -> dom::nodes::window_proxy*;
    auto active_document() -> dom::nodes::document*;
};

#endif //SBROWSER2_CONTEXT_INTERNALS_HPP
