module;
#include "ext/macros/language_shorthand.hpp"
#include <memory>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/split.hpp>
#include <tl/optional.hpp>


module apis.webappsec_permissions_policy.detail;
import apis.webappsec_permissions_policy.types;

import apis.dom.document;
import apis.dom.document_private;
import apis.dom.node;

import apis.html.types;
import apis.url.detail;

import ext.core;


auto webappsec_permissions_policy::detail::observable_policy(
        dom::node* node)
        -> std::unique_ptr<permissions_policy_t>
{
    // If the node is a Document then return a permissions policy object representing the PermissionsPolicy of the
    // Document node.
    if (decltype(auto) document = dom_cast<dom::document*>(node))
        return std::make_unique<permissions_policy_t>(*document->d_func()->permissions_policy);

    // Create a new permissions policy object as a unique_ptr, and set each feature in the 'inherited_policy' to the
    // result of defining an inherited policy for a fearure in a container at an origin, depeding on the feature, node,
    // and the observable origin of the node.
    auto policy = std::make_unique<permissions_policy_t>();

    for (auto&& feature: supported_features)
        policy->inherited_policy[feature] = detail::define_inherited_policy_for_feature_in_container_at_origin(feature, node, *declared_origin(node));

    // Return the newly created policy.
    return policy;
}


auto webappsec_permissions_policy::detail::construct_policy_from_dict_and_origin(
        ext::map<detail::feature_name_t, ext::any>&& dictionary,
        const html::detail::origin_t& origin)
        -> declared_policy_t
{
    // Create a declared policy, which will be the final policy that is returned. Iterating through the 'dictionary'
    // results in the keys/values being parsed into the 'policy'
    auto policy = declared_policy_t{};

    // Iterate throgh every key/value pair in the 'dictionary' -- this is the 'feature_name' and 'value' it corresponds
    // to. The value could be a string or vector of strings (any other type just fails the if-branches meaning that it
    // isn't parsed and there will be no entries in the delcared 'policy'.
    for (auto&& [feature_name, value]: dictionary)
    {
        // Create the corresponding policy controlled feature for the feature name (pointer to an object stored in the
        // global object (TODO). Define the 'allowlist' too.
        auto feature = std::make_unique<policy_controlled_feature_t>(feature_name);
        auto allowlist = allowlist_t{};

        // If the value is the special character "*" or a list which contains 1+ entries of a "*", then this means the
        // special case occurs where there is only a "*" in the 'allowlist' -- anything will match against it, so don't
        // bother adding any other filters (in the case of a vector of strings).
        if (value.to<ext::string>() == u"*" || ranges::contains(value.to<detail::allowlist_t>(), u"*"))
            allowlist.emplace_back(u"*");

        // If the value is the special string "self", then add the 'origin' parameter into the 'allowlist'. If the
        // "self" string in contained in a vector of strings, then the rest of the vector has to be handled too, so
        // consider this case in the vector case (below).
        else if (value.to<ext::string>() == u"self")
            allowlist.emplace_back(origin);

        // If the value in the ext::any type can be converted into a vector of strings (ie the 'allowlist_t' type), then
        // parse the string-representations of URLs into the 'policy', and handle the special "self" case too.
        else if (value.try_to<allowlist_t>())
        {
            for (auto&& element: value.to<allowlist_t>())
            {
                // For the special case "self", append the 'origin' to the 'allowlist' (same as above). Otherwise, parse
                // each 'element' of the 'value', and if the parsing doesn't result in a failure, and its origin isn't
                // opaque, append its origin to the 'allowlist'.
                if (value.to<ext::string>() == u"self") allowlist.emplace_back(origin);
                else if (auto result = url::detail::url_parser(std::move(element)); result.has_value() /* TODO */)
                    allowlist.emplace_back(result->d_func()->origin.get());
            }
        }

        // Set the 'policy's entry for 'feature' to the newly parsed-into 'allowlist' (use std::move as there is no need
        // to copy it).
        policy[feature] = std::move(allowlist);
    }

    // Return the created policy.
    return policy;
}


auto webappsec_permissions_policy::detail::parse_policy_directive(
        ext::string&& value,
        const html::detail::origin_t& origin,
        ext::optional<const html::detail::origin_t&>&& target_origin)
        -> policy_directive_t
{
    auto directive = policy_directive_t{};
    for (auto&& serialized_declaration: std::move(value) | ranges::views::split(';'))
    {
        auto tokens = serialized_declarations | ranges::views::split(' ');
        continue_if (tokens.empty());

        auto feature_name = tokens.front();
        continue_if (!magic_enum::enum_cast<feature_name_t>(feature_name).has_value());

        auto feature = std::make_unique<policy_controlled_feature_t>(magic_enum::enum_cast<feature_name_t>(feature_name));
        auto target_list = tokens | ranges::views::tail;
        auto allowlist = allowlist_t{};

        if (ranges::contains(allowlist, u"*"))
            allowlist = {u"*"}
        else
            ; // TODO
    }
}
