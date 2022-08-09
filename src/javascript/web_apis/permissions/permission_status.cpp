#include "permission_status.hpp"

#include "permissions/detail/permission_internals.hpp"

#include <magic_enum.hpp>


permissions::permission_status::permission_status()
{
    state._Meta._AttachEnumConstraint(magic_enum::enum_names<detail::permission_internals::permission_state_t>);
}
