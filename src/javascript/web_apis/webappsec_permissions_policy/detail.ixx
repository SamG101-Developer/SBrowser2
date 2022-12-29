module;
#include "ext/macros/pimpl.hpp"
#include <tl/optional.hpp>


export module apis.webappsec_permissions_policy.detail;
import apis.webappsec_permissions_policy.types;

import apis.dom.types;
import apis.html.types;
import ext.core;
import js.env.realms;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(webappsec_permissions_policy)
{
    // Non "abstract operation" detail method
    auto allowlist_matches(const allowlist_t& allowlist, const html::detail::origin_t& origin) -> ext::boolean;
    auto policy_allows_feature(const permissions_policy_t& policy, feature_name_t&& feature, const html::detail::origin_t& origin) -> ext::boolean;
    auto policy_allows_feature(const permissions_policy_t& policy, const policy_controlled_feature_t& feature, const html::detail::origin_t& origin) -> ext::boolean;
    auto observable_policy(dom::node* node) -> std::unique_ptr<permissions_policy_t>;
    auto declared_origin(dom::element*) -> std::unique_ptr<html::detail::origin_t>;

    // [9] Abstract operations
    /* [9.01] */ auto process_response_policy(const fetch::detail::response_t&, const html::detail::origin_t&) -> declared_policy_t;
    /* [9.02] */ auto construct_policy_from_dict_and_origin(ext::map<detail::feature_name_t, ext::any>&& dictionary, const html::detail::origin_t& origin) -> declared_policy_t;
    /* [9.03] */ auto parse_policy_directive(ext::string_view value, const html::detail::origin_t& container_origin, ext::optional<const html::detail::origin_t&>&& target_origin) -> policy_directive_t;
    /* [9.04] */ auto process_permissions_policy_attributes(dom::element* element) -> container_policy_t;
    /* [9.05] */ auto create_permissions_policy_for_browsing_context(const html::detail::browsing_context_t& browsing_context, const html::detail::origin_t& origin) -> std::unique_ptr<permissions_policy>;
    /* [9.06] */ auto create_permissions_policy_for_browsing_context_from_response(const html::detail::browsing_context_t& browsing_context, const html::detail::origin_t& origin, const fetch::detail::response_t&) -> std::unique_ptr<permissions_policy>;
    /* [9.07] */ auto define_inherited_policy_for_feature_in_browsing_context(detail::feature_name_t feature, const html::detail::origin_t& origin, html::detail::browsing_context_t& browsing_context) -> inherited_policy_t;
    /* [9.08] */ auto define_inherited_policy_for_feature_in_container_at_origin(detail::feature_name_t feature, dom::node* container, const html::detail::origin_t& origin) -> inherited_policy_t;
    /* [9.09] */ auto is_feature_enabled_in_document_for_origin(detail::feature_name_t feature, dom::document* document, const html::detail::origin_t& origin) -> inherited_policy_value_t;
    /* [9.10] */ auto generate_report_for_violation_of_permissions_policy_on_settings(detail::feature_name_t feature, js::env::env& environment, ext::string&& group = u"") -> void;
    /* [9.11] */ auto should_request_be_allowed_to_use_feature(detail::feature_name_t feature, const fetch::detail::fetch_t& request) -> ext::boolean;
}
