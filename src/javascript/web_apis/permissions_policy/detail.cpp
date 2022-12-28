module;
#include "ext/macros/language_shorthand.hpp"
#include <memory>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/for_each.hpp>


module apis.webappsec_permissions_policy.detail;
import apis.webappsec_permissions_policy.types;

import apis.dom.document;
import apis.dom.document_private;
import apis.dom.node;

import apis.html.types;

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
        policy->inherited_policy[feature] = detail::define_inherited_policy_for_feature_in_container_at_origin(feature, node, declared_origin(node));

    // Return the newly created policy.
    return policy;
}


auto webappsec_permissions_policy::detail::construct_policy_from_dict_and_origin(
        ext::map<detail::feature_name_t, ext::any>&& dictionary,
        const html::detail::origin_t& origin)
        -> declared_policy_t
{
    auto policy = declared_policy_t{};
    for (auto&& [feature_name, value]: dictionary)
    {
        auto feature = std::make_unique<policy_controlled_feature_t>(feature_name);
        auto allowlist = detail::allowlist_t{};

        if (value.to<ext::string>() == u"*" || ranges::contains(value.to<detail::allowlist_t>(), u"*"))
            allowlist.emplace_back(u"*");

        else if (value.to<ext::string>() == u"self")
            allowlist.emplace_back(origin);

        else if (value.try_to<allowlist_t>())
        {
            for (auto&& element: value.to<allowlist_t>())
            {
                if (value.to<ext::string>() == u"self")
                    allowlist.emplace_back(origin);
                else
                    result = url::detail::url_parser(std::move(element));
                if (result.has_value() && true /* TODO */)
                    allowlist.emplace_back(target);
            }
        }

        policy[feature] = std::move(allowlist);
    }

    return policy;
}
