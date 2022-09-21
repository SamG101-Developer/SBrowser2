#ifndef SBROWSER2_CONTEXT_INTERNALS_HPP
#define SBROWSER2_CONTEXT_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/pair.hpp"
#include "ext/vector.hpp"
#include <memory>

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)

namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace dom::nodes {class window;}
namespace dom::nodes {class window_proxy;}

namespace html::detail
{

    auto is_still_on_initial(
            const browsing_context_t& context)
            -> ext::boolean;

    template <callable F>
    auto navigate(
            const browsing_context_t& context,
            const browsing_context_t& source_context,
            ext::boolean exceptions_enabled = false,
            history_handling_behaviour_t history_handling_behaviour = history_handling_behaviour_t::DEFAULT,
            const html::detail::policy_container_t& history_policy_container = nullptr,
            ext::string_view navigation_type = "",
            ext::string_view navigation_id = "",
            F&& process_response_end_of_body = []() {})
            -> void;

    //

    auto set_active_document(
            detail::browsing_context_t& context,
            dom::nodes::document* document)
            -> void;

    auto determine_origin(
            detail::browsing_context_t& context,
            const url::detail::url_t& url,
            detail::sandboxing_flag_set_t sandbox_flags,
            const detail::origin_t& origin)
            -> detail::origin_t;

    auto create_new_browsing_context(
            dom::nodes::document* document,
            dom::nodes::element* embedder,
            detail::browsing_context_group_t& group)
            -> detail::browsing_context_t;

    auto create_new_top_level_browsing_context()
            -> detail::browsing_context_t;

    auto create_new_auxiliary_browsing_context(
            const detail::browsing_context_t& opener)
            -> detail::browsing_context_t;

    auto create_new_nested_browsing_context(
            dom::nodes::element* element)
            -> void;

    auto is_child_browsing_context(
            const detail::browsing_context_t& parent,
            const detail::browsing_context_t& potential_child)
            -> ext::boolean;

    auto is_document_tree_child_browsing_context(
            const detail::browsing_context_t& parent,
            const detail::browsing_context_t& potential_child)
            -> ext::boolean;

    auto descendant_browsing_contexts(
            dom::nodes::document* document)
            -> ext::vector<detail::browsing_context_t*>;

    auto is_ancestor_browsing_context(
            const browsing_context_t& context_a,
            const browsing_context_t& context_b)
            -> ext::boolean;

    auto ancestor_browsing_contexts(
            const browsing_context_t& context_a)
            -> ext::vector<browsing_context_t*>;

    auto is_top_level_browsing_context(
            const browsing_context_t& context)
            -> ext::boolean;

    auto document_family(
            const detail::browsing_context_t& context)
            -> ext::vector<detail::browsing_context_t*>;

    auto active_window(
            const detail::browsing_context_t& context)
            -> dom::nodes::window_proxy*;

    auto active_document(
            const detail::browsing_context_t& context)
            -> dom::nodes::document*;

    auto container_document(
            const detail::browsing_context_t& context)
            -> dom::nodes::document*;

    auto content_document(
            const detail::browsing_context_t& context)
            -> dom::nodes::document*;

    auto is_familiar_with(
            const detail::browsing_context_t& context_a,
            const detail::browsing_context_t& context_b)
            -> ext::boolean;

    auto is_allowed_to_navigate_to(
            const detail::browsing_context_t& context_a,
            const detail::browsing_context_t& context_b)
            -> ext::boolean;

    auto has_browsing_context_scope_origin(
            const detail::browsing_context_t& context)
            -> ext::boolean;

    auto create_new_browsing_context_group()
            -> detail::browsing_context_group_t;

    auto append_to_browsing_context_group(
            const detail::browsing_context_t& top_level_context)
            -> void;

    auto remove_from_browsing_context_group(
            const detail::browsing_context_t& top_level_context)
            -> void;

    auto is_valid_browsing_context_name(
            ext::string_view name)
            -> ext::boolean;

    auto is_valid_browsing_context_name_or_keyword(
            ext::string_view name)
            -> ext::boolean;

    auto choose_browsing_context(
            ext::string_view name,
            const browsing_context_t& context,
            ext::boolean noopener)
            -> ext::pair<browsing_context_t&, ext::string>;

    template <typename T>
    auto perform_security_check(
            T* platform_object,
            ext::string_view identifier,
            ext::string_view type)
            -> void;

    auto is_script_closable(
            const browsing_context_t& context)
            -> ext::boolean;

    auto number_of_document_tree_child_browsing_contexts(
            dom::nodes::window* window)
            -> ext::number<int>;

    auto document_tree_child_browsing_context_name_property_set(
            dom::nodes::window* window)
            -> ext::vector_view<ext::string>;

    auto discard(
            dom::nodes::document* document)
            -> void;

    auto discard(
            const detail::browsing_context_t& document)
            -> void;

    auto close_browsing_context(
            const detail::browsing_context_t& document)
            -> void;
}


struct html::detail::browsing_context_group_t
{
    // TODO : agent-cluster-map
    // TODO : historical-agent-cluster-map

    detail::cross_origin_isolation_mode_t cross_origin_isolation_mode;
    detail::browsing_context_set_t browsing_context_set;

    auto operator->() -> decltype(auto) {return std::addressof(browsing_context_set);}
};


struct html::detail::browsing_context_t
{
    dom::nodes::window_proxy* window_proxy;
    browsing_context_t* opener_browsing_context;
    ext::boolean disowned;
    ext::boolean is_closing;

    ext::number<int> virtual_browsing_context_group_id;
    std::unique_ptr<url::detail::url_t> initial_url;
    std::unique_ptr<detail::origin_t> m_opener_origin_at_creation;

    std::unique_ptr<detail::origin_t> creator_origin;
    std::unique_ptr<url::detail::url_t> creator_url;
    std::unique_ptr<url::detail::url_t> creator_base_url;

    browsing_context_t* parent_browsing_context;
    ext::set<browsing_context_t*> group;
    ext::boolean is_popup;

    ext::string browsing_context_name;

    sandboxing_flag_set_t popup_sandboxing_set;

    ext::vector<dom::nodes::document*> session_history {};

private:
    /* CONTACT_PICKER */
    ext::boolean m_contact_picker_is_showing = false;
};

#endif //SBROWSER2_CONTEXT_INTERNALS_HPP
