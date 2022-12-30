module;
#include "ext/macros.hpp"
#include "javascript/macros/expose.hpp"


export module apis.permissions.permissions:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(permissions, permissions)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(permissions);
};
