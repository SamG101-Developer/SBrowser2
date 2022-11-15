#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ARIA_MIXINS_ARIA_MIXIN_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ARIA_MIXINS_ARIA_MIXIN_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(aria::mixins, aria_mixin) : virtual dom_object_private
{
    MAKE_QIMPL(aria_mixin);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ARIA_MIXINS_ARIA_MIXIN_PRIVATE_HPP
