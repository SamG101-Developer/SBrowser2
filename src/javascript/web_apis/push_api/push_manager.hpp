#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace push_api {class push_manager;}
namespace push_api {class push_manager_private;}

// Other Includes & Forward Declarations


class push_api::push_manager
        : public dom_object
{
public constructors:
    MAKE_PIMPL(push_manager);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_MANAGER_HPP
