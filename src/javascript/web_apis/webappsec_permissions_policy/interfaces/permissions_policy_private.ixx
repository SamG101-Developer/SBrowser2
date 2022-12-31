module;
#include "ext/macros.hpp"


export module apis.webappsec_permissions_policy.permissions_policy:p;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);
IMPORT_ALL_TYPES(html);
IMPORT_ALL_TYPES(webappsec_permissions_policy);


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
