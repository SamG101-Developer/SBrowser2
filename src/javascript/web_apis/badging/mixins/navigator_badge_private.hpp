#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_MIXINS_NAVIGATOR_BADGE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_MIXINS_NAVIGATOR_BADGE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(badging::mixins, navigator_badge)
        : virtual dom_object_private
{
    MAKE_QIMPL(navigator_badge);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_MIXINS_NAVIGATOR_BADGE_PRIVATE_HPP
