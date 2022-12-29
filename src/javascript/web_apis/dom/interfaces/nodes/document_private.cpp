module;
#include "ext/macros/pimpl.hpp"

module apis.dom.document_private;


dom::document_private::documnt_private()
        : permissions_policy{std::make_unique<webappsec_permissions_policy>()}
{
    ACCESS_QIMPL;
    permissions_policy->d_func()->associated_node = q;
}
