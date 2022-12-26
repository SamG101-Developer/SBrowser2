module;
#include "ext/macros/language_shorthand.hpp"
#include <memory>
#include <range/v3/vie


module apis.webappsec_permissions_policy.detail;
import apis.webappsec_permissions_policy.types;

import apis.dom.document;
import apis.dom.document_private;
import apis.dom.node;

import ext.core;


auto webappsec_permissions_policy::detail::observable_policy(
        dom::node* node)
        -> std::unique_ptr<permissions_policy_t>
{
    if (decltype(auto) document = dom_cast<dom::document*>(node))
        return std::make_unique<permissions_policy_t>(*document->d_func()->permissions_policy);

    auto inherited_policy = inherited_policy_t{};
    auto declared_policy = declared_policy_t{};

    supported_features
            | ranges::views::filter(ext::bind_back(&detail::define_inherited_policy_for_feature_in_container_at_origin, node, declared_origin(node)))
            | ranges::views::for_each()
}
