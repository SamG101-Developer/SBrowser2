#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace push_api {class push_subscription;}
namespace push_api {class push_subscription_private;}

// Other Includes & Forward Declarations


class push_api::push_subscription
        : virtual public dom_object
{
public constructors:
    MAKE_PIMPL(push_subscription);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_SUBSCRIPTION_HPP
