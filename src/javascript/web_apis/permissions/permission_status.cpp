#include "permission_status.hpp"

#include "ext/assertion.hpp"

#include "permissions/detail/permission_internals.hpp"

#include <magic_enum.hpp>


permissions::permission_status::permission_status()
{
    state._Meta._AttachEnumConstraint(magic_enum::enum_names<detail::permission_state_t>);
}


permissions::permission_status::permission_status(
        detail::permissions_descriptor_t&& permission_descriptor)
{
    using permissions_policy::detail::feature_t;

    // make sure that the feature is supported by checking if the optional value resulting from tehe num case oholds a
    // value or not
    using permissions::detail::powerful_feature_t;

    ASSERT(
            magic_enum::enum_cast<feature_t>(permission_descriptor.at("name").to<powerful_feature_t>().name).has_value(),
            "Feature must be supported",
            permission_descriptor.at("name").to<powerful_feature_t>().name);

    // set the [[query]] slot to the permission descriptor
    s_query = std::move(permission_descriptor);
}
