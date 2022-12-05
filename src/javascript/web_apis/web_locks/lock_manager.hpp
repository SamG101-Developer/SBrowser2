#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_MANAGER_HPP

// Inheritance Includes & This Class

namespace web_locks {class lock_manager;}
namespace web_locks {class lock_manager_private;}

// Other Includes & Forward Declarations

#include INCLUDE_INNER_TYPES(web_locks)


class web_locks::lock_manager
        : virtual public dom_object
{
public constructors:
    lock_manager();
    MAKE_PIMPL(lock_manager);
    MAKE_V8_AVAILABLE(WINDOW | WORKER | SECURE);

public js_methods:
    auto request(ext::string_view name, detail::lock_granted_callback_t&& callback, detail::lock_options_t&& options = {}) -> ext::promise<ext::any>;
    auto query() -> ext::promise<detail::lock_manager_snapshot_t>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_LOCKS_LOCK_MANAGER_HPP
