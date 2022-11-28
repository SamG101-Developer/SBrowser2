#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace web_locks {class lock;}
namespace web_locks {class lock_private;}

// Other Includes & Forward Declarations#
#include INCLUDE_INNER_TYPES(web_locks)


class web_locks::lock
        : virtual public dom_object
{
public constructors:
    lock();
    MAKE_PIMPL(lock);
    MAKE_V8_AVAILABLE(WINDOW | WORKER | SECURE);

public js_properties:
    DEFINE_GETTER(name, ext::view_of_t<detail::resource_name_t>);
    DEFINE_GETTER(mode, detail::lock_mode_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_HPP
