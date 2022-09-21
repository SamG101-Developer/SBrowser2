#pragma once
#ifndef SBROWSER2_PERMISSIONS_POLICY_HPP
#define SBROWSER2_PERMISSIONS_POLICY_HPP

#include "dom_object.hpp"
namespace permissions_policy {class permissions_policy_object;}

#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(permissions_policy)
namespace dom::nodes {class node;}


class permissions_policy::permissions_policy_object
        : public virtual dom_object
{
public js_methods:
    auto allows_feature(detail::feature_name_t&& feature, ext::string&& origin = "") -> ext::boolean;
    auto features() -> ext::set<ext::string>;
    auto allowed_features() -> ext::set<ext::string>;
    auto get_allowlist_for_feature(detail::feature_name_t&& feature) -> ext::set<ext::string>;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_methods:
    [[nodiscard]] auto m_default_origin() const -> ext::string;

private cpp_properties:
    dom::nodes::node* m_associated_node;
};


#endif //SBROWSER2_PERMISSIONS_POLICY_HPP
