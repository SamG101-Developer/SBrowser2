#pragma once
#ifndef SBROWSER2_PERMISSIONS_POLICY_HPP
#define SBROWSER2_PERMISSIONS_POLICY_HPP

#include "dom_object.hpp"
namespace permissions_policy {class permissions_policy;}

#include "ext/vector.hpp"


class permissions_policy::permissions_policy
        : public virtual web_apis::dom_object
{
public js_methods:
    auto allows_feature(ext::string_view feature, ext::string_view origin = "") -> ext::boolean;
    auto features() -> ext::string_vector;
    auto allowed_features() -> ext::string_vector;
    auto get_allowlist_for_feature(ext::string_view feature) -> ext::string_vector;
};


#endif //SBROWSER2_PERMISSIONS_POLICY_HPP
