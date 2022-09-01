#pragma once
#include "dom/nodes/event_target.hpp"
#include "dom_object.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FOCUS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FOCUS_INTERNALS_HPP

#include "ext/keywords.hpp"
#include USE_CONCEPTS(html)
#include USE_INNER_TYPES(html)

namespace dom::nodes {class element;}
namespace dom::nodes {class node;}


namespace html::detail
{
    auto dom_anchor(
            concepts::focusable_area auto* area)
            -> dom::nodes::node*;

    auto currently_focused_area_of_top_level_browsing_context(
            const html::detail::browsing_context_t& context)
            -> concepts::focusable_area auto*;

    auto current_focus_chain_of_top_level_browsing_context(
            const html::detail::browsing_context_t& context)
            -> concepts::focusable_area auto*;

    auto focus_chain(
            concepts::focusable_area auto* area)
            -> ext::vector<ext::any>; // TODO

    auto is_sequentially_focusable(
            concepts::focusable_area auto* area)
            -> ext::boolean;

    auto is_click_focusable(
            concepts::focusable_area auto* area)
            -> ext::boolean;

    auto is_focus_navigation_scope_owner(
            dom::nodes::node* node)
            -> ext::boolean;

    auto associated_focus_navigation_owner(
            dom::nodes::element* element)
            -> dom::nodes::node*;

    auto focus_navigation_scope(
            dom::nodes::node* node)
            -> ext::vector<dom::nodes::node*>;

    auto focus_delegate(
            dom::nodes::node* focus_target,
            ext::string_view focus_trigger = "other")
            -> concepts::focusable_area auto*;

    auto auto_focus_delegate(
            dom::nodes::node* focus_target,
            ext::string_view focus_trigger = "other")
            -> concepts::focusable_area auto*;

    auto focusing_steps(
            concepts::focusable_area auto* area)
            -> void;

    auto focusing_steps(
            const browsing_context_t& context)
            -> void;

    auto unfocusing_steps(
            concepts::focusable_area auto* area)
            -> void;

    auto focus_update_steps(
            ext::vector_view<ext::any> old_chain,
            ext::vector_view<ext::any> new_chain,
            concepts::focusable_area auto* new_focus_target)
            -> void;

    auto has_focus_steps(
            dom::nodes::document* document)
            -> ext::boolean;

    auto fire_focus_event(
            ext::string&& e,
            dom::nodes::event_target* element,
            dom::nodes::event_target* related_target)
            -> void;

    auto flush_autofocus_candidates(
            dom::nodes::document* document)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_FOCUS_INTERNALS_HPP
