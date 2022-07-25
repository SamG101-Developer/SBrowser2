#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/property.hpp"
#include "permissions_policy/_typedefs.hpp"
#include <v8-object.h>
namespace dom::nodes {class document;}
namespace dom::nodes {class element;}
namespace html::detail::context_internals {struct browsing_context;}
namespace html::elements {class html_element;}
namespace fetch::detail::request_internals {struct internal_request;}
namespace fetch::detail::response_internals {struct internal_response;}
namespace permissions_policy::detail::policy_internals {struct internal_permissions_policy;}
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
        {T::allow} -> std::same_as<ext::property<ext::string, _T>&>;
    };

    auto is_valid_feature(
            ext::string_view feature_name)
            -> ext::boolean;

    auto default_allowlist(
            feature_t feature)
            -> allowlist_t;

    auto allow_list_origin_matches(
            allowlist_t allowlist0,
            allowlist_t allowlist1)
            -> ext::boolean;

    auto process_response_body(
            const fetch::detail::response_internals::internal_response& response,
            ext::string&& origin)
            -> declared_policy_t;

    auto construct_policy_from_dictionary_and_origin(
            ext::map_view<ext::string, ext::vector<ext::string>> dictionary,
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
            html::detail::context_internals::browsing_context& context,
            ext::string&& origin)
            -> policy_internals::internal_permissions_policy;
    
    auto create_permissions_policy_for_feature_in_container_at_origin(
            const allowable_element auto* allowable_element,
            ext::string&& origin)
            -> policy_internals::internal_permissions_policy;

    auto create_permissions_policy_for_browsing_context_from_response(
            html::detail::context_internals::browsing_context& context,
            ext::string&& origin,
            fetch::detail::response_internals::internal_response& response)
            -> policy_internals::internal_permissions_policy;

    auto define_inherited_policy_for_feature_in_browsing_context(
            feature_t feature,
            ext::string&& origin,
            html::detail::context_internals::browsing_context& context)
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
            fetch::detail::request_internals::internal_request& request)
            -> ext::boolean;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERMISSIONS_POLICY_DETAIL_ALGORITHM_INTERNALS_HPP
