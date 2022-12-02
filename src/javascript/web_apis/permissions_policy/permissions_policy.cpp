#include "permissions_policy.hpp"

#include "ext/casting.ixx"
#include "dom/nodes/document.hpp"

#include "html/elements/html_iframe_element.hpp"

#include "permissions_policy/detail/algorithm_internals.hpp"
#include "permissions_policy/detail/policy_internals.hpp"

#include <magic_enum.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/to_container.hpp>


auto permissions_policy::permissions_policy_object::allows_feature(
        detail::feature_name_t&& feature,
        ext::string&& origin)
        -> ext::boolean
{
    // if the origin is empty, then set it to the default origin, which is dependent on whether the associated node is an
    // Element of Document. the policy is teh observable policy for the correctly cast associated node
    origin = origin ?: m_default_origin();
    auto policy = detail::observable_policy(m_associated_node);

    using enum detail::inherited_policy_value_t;
    auto feature_enum = magic_enum::enum_cast<detail::feature_t>(std::move(feature));
    return_if(!feature_enum.has_value()) false;
    return policy.inherited_policy.at(*feature_enum) == ENABLED;
}


auto permissions_policy::permissions_policy_object::features()
        -> ext::set<ext::string>
{
    // take all the supported features (in a clas-scoped enumeration), get all the entries with 'magic_enum', take the
    // enum values (exclude heir indexes), and transform them into their string representations of the enum values,
    // before converting the range into the desired type
    auto features = magic_enum::enum_entries<detail::feature_t>();
    return features
            | ranges::views::values
            | ranges::to<ext::set<ext::string>>;
}


auto permissions_policy::permissions_policy_object::allowed_features()
        -> ext::set<ext::string>
{
    using enum detail::inherited_policy_value_t;

    auto origin = m_default_origin();
    auto policy = detail::observable_policy(m_associated_node);

    // filter the features to only allow the ENABLED features, then take the feature names from the pairs, and get their
    // string forms; finally convert the range back into a set of strings and return them
    return policy.inherited_policy
            | ranges::views::filter(ext::bind_back(ext::pair_val_matches{}, ENABLED))
            | ranges::views::keys
            | ranges::views::transform(magic_enum::enum_name<detail::feature_t>)
            | ranges::to<ext::set<ext::string>>;
}


auto permissions_policy::permissions_policy_object::get_allowlist_for_feature(
        detail::feature_name_t&& feature)
        -> ext::set<ext::string>
{
    using enum detail::inherited_policy_value_t;

    auto origin = m_default_origin();
    auto policy = detail::observable_policy(m_associated_node);

    // return an empty set if the feature doesn't exist, or the value is disabled in the policy
    auto feature_enum = magic_enum::enum_cast<detail::feature_t>(std::move(feature));
    return_if(!feature_enum.has_value()) {};
    return_if(policy.inherited_policy.at(*feature_enum) == DISABLED) {};

    auto allowlist = policy.declared_policy.at(*feature_enum);
    return ranges::contains(allowlist, "*")
            ? allowlist
            : allowlist | ranges::views::transform(html::detail::serialize_origin) | ranges::to<detail::allowlist_t>;
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
