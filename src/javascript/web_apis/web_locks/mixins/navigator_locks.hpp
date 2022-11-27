#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_MIXINS_NAVIGATOR_LOCKS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_MIXINS_NAVIGATOR_LOCKS_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace web_locks::mixins {class navigator_locks;}
namespace web_locks::mixins {class navigator_locks_private;}

// Other Includes & Forward Declarations
namespace web_locks {class lock_manager;}


class web_locks::mixins::navigator_locks
        : virtual public dom_object
{
public constructors:
    navigator_locks();
    MAKE_PIMPL(navigator_locks);
    MAKE_V8_AVAILABLE(ALL | SECURE);

public js_properties:
    DEFINE_GETTER(locks, lock_manager*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_MIXINS_NAVIGATOR_LOCKS_HPP
