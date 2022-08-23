#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/property.hpp"
#include <v8-object.h>
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(permissions_policy)
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace html::elements {class html_element;}
namespace url {class url_object;}

/*
 * TODO : FEATURE_NAME enumeration
 * TODO : validate feature names tries to cast the string to the FEATURE_NAME enum type
 */

namespace permissions_policy::detail::algorithm_internals
{
    template <typename T>
    concept allowable_element = requires
    {
        requires std::is_base_of_v<html::elements::html_element, T>;
        {T::allow} -> std::same_as<ext::property<ext::string, true>&>;
    };

    auto is_valid_feature(
            const feature_name_t& feature_name)
            -> ext::boolean;

    auto default_allowlist(
            feature_t feature)
            -> allowlist_t;

    auto allow_list_origin_matches(
            allowlist_t allowlist0,
            allowlist_t allowlist1)
            -> ext::boolean;

    auto process_response_body(
            const fetch::detail::response_t& response,
            ext::string&& origin)
            -> declared_policy_t;

    auto construct_policy_from_dictionary_and_origin(
            ext::map_view<feature_name_t, ext::vector<ext::string>> dictionary,
            ext::string&& origin)
            -> declared_policy_t;

    auto parse_policy_directive(
            ext::string&& value,
            ext::string&& origin,
            ext::string&& target_origin = "")
            -> policy_directive_t;

    auto process_permissions_policy_attributes(
            const allowable_element auto* element)
            -> container_policy_t;

    auto create_permissions_policy_for_browsing_context(
            html::detail::browsing_context_t& context,
            ext::string&& origin)
            -> internal_permissions_policy_t;
    
    auto create_permissions_policy_for_feature_in_container_at_origin(
            const allowable_element auto* allowable_element,
            ext::string&& origin)
            -> internal_permissions_policy_t;

    auto create_permissions_policy_for_browsing_context_from_response(
            html::detail::browsing_context_t& context,
            ext::string&& origin,
            fetch::detail::response_t& response)
            -> internal_permissions_policy_t;

    auto define_inherited_policy_for_feature_in_browsing_context(
            feature_t feature,
            ext::string&& origin,
            html::detail::browsing_context_t& context)
            -> inherited_policy_value_t;

    auto define_inherited_policy_for_feature_in_container_at_origin(
            feature_t feature,
            const allowable_element auto* context_container,
            ext::string&& origin)
            -> inherited_policy_value_t;

    auto is_feature_enabled_in_document_for_origin(
            feature_t feature,
            dom::nodes::document* document,
            ext::string&& origin)
            -> inherited_policy_value_t;

    auto generate_report_for_violation_of_permissions_policy_on_settings(
            feature_t feature,
            v8::Local<v8::Object> settings,
            ext::string&& group = "")
            -> void;

    auto should_request_be_allowed_to_use_feature(
            feature_t feature,
            fetch::detail::request_t& request)
            -> ext::boolean;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_ALGORITHM_INTERNALS_HPP
