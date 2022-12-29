module;
#include "ext/macros/pimpl.hpp"


export module apis.permissions.permission_status_private;
import apis.dom.event_target_private;

import apis.permissions.types;
import ext.core;


DEFINE_PRIVATE_CLASS(permissions, permission_status)
        : dom::event_target_private
{
public:
    MAKE_QIMPL(permission_status);

public:
    detail::permission_descriptor_type query;
    detail::permission_state_t state;
    ext::string name;
};
