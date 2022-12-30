module;
#include "ext/macros.hpp"


export module apis.aria.mixins.aria_mixin:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(aria::mixins, aria_mixin)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(aria_mixin);
};
