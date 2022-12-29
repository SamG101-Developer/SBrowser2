module;
#include "ext/macros/macros.hpp"


export module apis.aria.mixins.aria_mixin_private;
import apis.dom_object_private;


DEFINE_PRIVATE_CLASS(aria::mixins, aria_mixin)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(aria_mixin);
};
