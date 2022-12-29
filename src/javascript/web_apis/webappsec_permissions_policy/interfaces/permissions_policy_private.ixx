module;
#include "ext/macros/macros.hpp"


export module apis.webappsec_permissions_policy.permissions_policy_private;
import apis.dom_object_private;

import apis.dom.types;
import apis.html.types;
import apis.webappsec_permissions_policy.types;
import ext.core;


DEFINE_PRIVATE_CLASS(webappsec_permissions_policy, permissions_policy)
        : virtual public dom_object_private
{
public:
    MAKE_QIMPL(permissions_policy);

public:
    auto default_origin() -> std::unique_ptr<html::detail::origin_t>;

public:
    std::observer_ptr<dom::node> associated_node;
};
