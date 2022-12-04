#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_WAKE_LOCK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_WAKE_LOCK_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace screen_wake_lock {class wake_lock;}
namespace screen_wake_lock {class wake_lock_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(screen_wake_lock)
#include "ext/promise.ixx"
namespace screen_wake_lock {class wake_lock_sentinel;}


class screen_wake_lock::wake_lock
        : public dom_object
{
public constructors:
    wake_lock();
    MAKE_PIMPL(wake_lock);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto request(detail::wake_lock_type type = detail::SCRREN) -> ext::promise<wake_lock_sentinel>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_WAKE_LOCK_HPP
