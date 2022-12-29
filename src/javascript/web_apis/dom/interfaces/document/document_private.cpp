module;
#include "ext/macros.hpp"

module apis.dom.document:p;


dom::document_private::documnt_private()
        : permissions_policy{std::make_unique<webappsec_permissions_policy>()}
{
    ACCESS_QIMPL;
    permissions_policy->d_func()->associated_node = q;
}
