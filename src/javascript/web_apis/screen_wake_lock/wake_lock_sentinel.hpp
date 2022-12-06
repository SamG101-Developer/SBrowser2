#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_WAKE_LOCK_SENTINEL_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_WAKE_LOCK_SENTINEL_HPP

// Inheritance Includes & This Class

namespace screen_wake_lock {class wake_lock_sentinel;}
namespace screen_wake_lock {class wake_lock_sentinel_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(screen_wake_lock)



class screen_wake_lock::wake_lock_sentinel
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(wake_lock_sentinel);
    MAKE_PIMPL(wake_lock_sentinel);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto release() -> ext::promise<void>;

public js_properties:
    DEFINE_GETTER(released, ext::boolean);
    DEFINE_GETTER(type, detail::wake_lock_type);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SCREEN_WAKE_LOCK_WAKE_LOCK_SENTINEL_HPP
