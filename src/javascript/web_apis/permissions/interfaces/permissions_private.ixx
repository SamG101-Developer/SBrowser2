module;
#include "ext/macros/macros.hpp"
#include "javascript/macros/expose.hpp"


export module apis.permissions.permissions_private;
import apis.dom_object_private;


DEFINE_PRIVATE_CLASS(permissions, permissions)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(permissions);
};
