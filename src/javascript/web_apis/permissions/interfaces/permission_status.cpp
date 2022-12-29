module;
#include "ext/macros/macros.hpp"


module apis.permissions.permission_status;
import apis.permissions.permission_status_private;
import apis.permissions.types;

import apis.webappsec_permissions_policy.types;

import ext.core;


permissions::permission_status::permission_status(
        detail::permissions_descriptor_t&& permission_descriptor)
{
    INIT_PIMPL; ACCESS_PIMPL;

    // Make sure that the feature is supported by checking if the optional value resulting from tehe num case oholds a
    // value or not
    auto feature_name = std::move(permission_descriptor[u"name"].to<webappsec_permissions_policy::detail::feature_name_t>());
    auto feature = webappsec_permissions_policy::detail::policy_controlled_feature_t::from_enum(feature_name);
    ext::assert_(feature);

    // Set the [[query]] slot to the permission descriptor
    d->name = permission_descriptor[u"name"];
    d->query = std::move(permission_descriptor);
}


auto permissions::permission_status::get_name() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->name;
}


auto permissions::permission_status::get_state() const -> detail::permission_state_t
{
    ACCESS_PIMPL;
    return d->state;
}
