module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <magic_enum.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>


module apis.webappsec_permissions_policy.permissions_policy;
import apis.webappsec_permissions_policy.permissions_policy_private;
import apis.webappsec_permissions_policy.detail;
import apis.webappsec_permissions_policy.types;

import ext.core;


auto webappsec_permissions_policy::permissions_policy::allows_feature(
        detail::feature_name_t&& feature,
        ext::string&& origin)
        -> ext::boolean
{
    ACCESS_PIMPL;

    // If the origin is empty, then set it to the default origin, which is dependent on whether the associated node is
    // an Element of Document. The policy is the observable policy for the correctly cast associated node.
    origin = origin ?: html::detail::serialize_origin(d->default_origin());
    auto policy = detail::observable_policy(d->associated_node.get());
    return detail::policy_allows_feature(*policy, std::move(feature), std::move(origin));
}


auto webappsec_permissions_policy::permissions_policy::features() -> ext::span<detail::feature_name_t>
{
    // take all the supported features (in a clas-scoped enumeration), get all the entries with 'magic_enum', take the
    // enum values (exclude heir indexes), and transform them into their string representations of the enum values,
    // before converting the range into the desired type
    return detail::supported_features;
}


auto webappsec_permissions_policy::permissions_policy::allowed_features() -> ext::set<ext::string>
{
    ACCESS_PIMPL;

    auto origin = d->default_origin();
    auto policy = detail::observable_policy(d->associated_node.get());

    return detail::supported_features
            | ranges::views::filter(ext::bind_front(&detail::policy_allows_feature, *policy, *origin))
            | ranges::to_set;
}


auto webappsec_permissions_policy::permissions_policy::get_allowlist_for_feature(
        detail::feature_name_t&& feature)
        -> ext::set<ext::string>
{
    ACCESS_PIMPL;

    auto origin = d->default_origin();
    auto policy = detail::observable_policy(d->associated_node.get());

    return_if (!detail::policy_allows_feature(*policy, std::move(feature), *origin)) {};

    // return an empty set if the feature doesn't exist, or the value is disabled in the policy
    auto feature_enum = magic_enum::enum_cast<detail::feature_t>(std::move(feature));
    return_if(!feature_enum.has_value()) {};
    return_if(policy->inherited_policy.at(*feature_enum) == DISABLED) {};

    auto allowlist = policy->declared_policy.at(/* TODO */);
    return ranges::contains(allowlist, u"*")
            ? allowlist
            : allowlist | ranges::views::transform(html::detail::serialize_origin) | ranges::to_set;
}


auto permissions_policy::permissions_policy_object::m_default_origin()
        const -> ext::string
{
    // check which type of node the associated node is; do it this way to avoid a possible extra dynamic_Cast<T>(...),
    // as this is a more expensive operation than checking the 'node_type' of the associated node
    auto is_document_node = m_associated_node->node_type() == dom::nodes::node::DOCUMENT_NODE;
    auto is_element_node = m_associated_node->node_type() == dom::nodes::node::ELEMENT_NODE;
    ASSERT(is_document_node || is_element_node);

    // return the document's origin if the associated node is a Document, the declared origin if the associated node is
    // an Element, otherwise an empty string
    return is_document_node
            ? dynamic_cast<dom::nodes::document*>(m_associated_node)->m_origin
            : detail::declared_origin(dynamic_cast<html::elements::html_iframe_element*>(m_associated_node));
}


auto permissions_policy::permissions_policy_object::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<permissions_policy_object>{isolate}
        .inherit<dom_object>()
        .function("allowsFeature", &permissions_policy_object::allows_feature)
        .function("features", &permissions_policy_object::features)
        .function("allowedFeatures", &permissions_policy_object::allowed_features)
        .function("getAllowlistForFeature", &permissions_policy_object::get_allowlist_for_feature)
        .auto_wrap_objects();
}
