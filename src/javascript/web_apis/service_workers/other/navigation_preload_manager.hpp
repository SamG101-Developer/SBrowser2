#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_OTHER_NAVIGATION_PRELOAD_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_OTHER_NAVIGATION_PRELOAD_MANAGER_HPP

#include "dom_object.hpp"
namespace service_workers::other {class navigation_preload_manager;}
namespace service_workers::other {class navigation_preload_manager_private;}

#include "ext/promise.ixx"
#include INCLUDE_INNER_TYPES(service_workers)


class service_workers::other::navigation_preload_manager
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(navigation_preload_manager);
    MAKE_PIMPL(navigation_preload_manager);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto enable() -> ext::promise<void>;
    auto disable() -> ext::promise<void>;
    auto set_header_value(ext::string&& value) -> ext::promise<void>;
    auto get_state() -> ext::promise<detail::navigation_preload_state_t>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SERVICE_WORKERS_OTHER_NAVIGATION_PRELOAD_MANAGER_HPP
